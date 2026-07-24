/**
 * @file    cmd_debug.cpp
 * @brief   便于在终端调试新功能的命令
 * @author  BitWalker
 * @version 1.0.0
 * @date    2026-07-19
 *
 */

#include "shell/shell_port.h"
#include "shell.h"
#include "memory/memory_seg.h"
#include "peripheral/User_DWT.hpp"
#include <string>



#ifdef __cplusplus
extern "C" {
#endif


/* 函数 --------------------------------------------------------------- */
int shellDebug(int argc, char *argv[])
{
    Shell *s = shellGetCurrent();
    if (!s) return -1;
    shellClear();

    shellPrint(s, "================== 开始测试 ================== \r\n\r\n");

    /* 终端输入段 ------------------------------------------------------ */

    shellPrint(s, "input_num = ");

    uint16_t input_num = 0;
    char prompt[32] = "%uhd";
    shellScan(s, prompt, &input_num);


    /* 终端输入段 ------------------------------------------------------ */

    // 完全禁用中断，这是一个危险的操作
    // 请确保测试的代码足够短
    #define DISABLE_IRQ
    #ifdef DISABLE_IRQ
    __disable_irq();
    #endif

    User_DWT::Clear();
    /* 性能统计段 ------------------------------------------------------ */

    input_num *= 2;
    input_num += 1;

    /* 性能统计段 ------------------------------------------------------ */
    auto const counter = User_DWT::GetCounter();

    #ifdef DISABLE_IRQ
    __enable_irq();
    #endif

    /* 终端输出段 ------------------------------------------------------ */

    shellPrint(s, "input_num * 2 + 1 = %d \r\n", input_num);

    /* 终端输出段 ------------------------------------------------------ */

    shellPrint(s, "\r\n================== 性能统计 ================== \r\n");

    // NOLINTNEXTLINE
    auto const ns = static_cast<float>((static_cast<uint64_t>(counter) * 1000000000ULL / static_cast<uint64_t>(HAL_RCC_GetSysClockFreq())));
    // NOLINTNEXTLINE
    auto const us = static_cast<float>((static_cast<uint64_t>(counter) * 1000000ULL / static_cast<uint64_t>(HAL_RCC_GetSysClockFreq())));

    shellPrint(s, "核心频率：%d MHz\r\n", HAL_RCC_GetSysClockFreq() / 1000000);
    shellPrint(s, "时钟周期：%d\r\n", counter);
    shellPrint(s, "测试耗时：%.3f ns\r\n", ns);
    shellPrint(s, "测试耗时：%.6f us\r\n", us);

    shellPrint(s, "\r\n================== 测试结束 ================== \r\n");


    return 0;
}

#ifdef __cplusplus
}
#endif
