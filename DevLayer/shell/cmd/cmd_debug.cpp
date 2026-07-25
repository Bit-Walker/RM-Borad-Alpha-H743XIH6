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
#include "dsp/fast_math_functions.h"


// 启用将在测试时完全禁用中断，这是一个危险的操作
// 请确保测试的代码足够短
#define DISABLE_IRQ


// 实际测试次数为 TEST_HALF_NUM * 2
#define TEST_HALF_NUM 500000


#ifdef __cplusplus
extern "C" {
#endif


/* 函数 --------------------------------------------------------------- */
ITCMRAM int shellDebug(int argc, char *argv[])
{
    Shell *s = shellGetCurrent();
    if (!s) return -1;
    shellClear();

    shellPrint(s, "================== 开始测试 ================== \r\n\r\n");


    /* 终端输入段 ---------------------------------------------------------- */

    float input_num {0.0};
    volatile float output_num {0.0};

    shellPrint(s, "input_num = ");

    char prompt[16] = "%f";
    shellScan(s, prompt, &input_num);

    /* 终端输入段 ---------------------------------------------------------- */


    /* 性能统计段 ---------------------------------------------------------- */

    constexpr float deg_to_rad = 3.14159265358979323846F / 180.0F;

    #define SHELL_DEBUG_PROCESS \
        output_num = arm_sin_f32(input_num * deg_to_rad);


    /* 性能统计段 ---------------------------------------------------------- */

    uint32_t counter     {0};
    uint64_t counter_sum {0};

    for (int i = 0; i < TEST_HALF_NUM; i++) {
        #ifdef DISABLE_IRQ
        __disable_irq();
        #endif
        User_DWT::Clear();

        __asm__("nop");
        SHELL_DEBUG_PROCESS
        __asm__("nop");

        counter = User_DWT::GetCounter();
        #ifdef DISABLE_IRQ
        __enable_irq();
        #endif
        counter_sum += counter;
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        #ifdef DISABLE_IRQ
        __disable_irq();
        #endif
        User_DWT::Clear();

        __asm__("nop");
        SHELL_DEBUG_PROCESS
        __asm__("nop");
        __asm__("nop");

        counter = User_DWT::GetCounter();
        #ifdef DISABLE_IRQ
        __enable_irq();
        #endif
        counter_sum += counter;
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        __asm__("nop");
        portYIELD();
    }


    /* 终端输出段 ---------------------------------------------------------- */

    shellPrint(s, "output_num = %.4f \r\n", output_num);

    /* 终端输出段 ---------------------------------------------------------- */


    shellPrint(s, "\r\n================== 性能统计 ================== \r\n\r\n");

    constexpr double test_num = 2.0 * TEST_HALF_NUM;

    //NOLINTNEXTLINE
    const float ns = static_cast<float>(static_cast<double>(counter_sum) / test_num *
        1000000000.0 / static_cast<double>(HAL_RCC_GetSysClockFreq()));

    //NOLINTNEXTLINE
    const float us = static_cast<float>(static_cast<double>(counter_sum) / test_num *
        1000000.0 / static_cast<double>(HAL_RCC_GetSysClockFreq()));

    //NOLINTNEXTLINE
    const float ms = static_cast<float>(static_cast<double>(counter_sum) / test_num *
        1000.0 / static_cast<double>(HAL_RCC_GetSysClockFreq()));

    shellPrint(s, "核心频率：%d MHz \r\n", HAL_RCC_GetSysClockFreq() / 1000000ULL);
    shellPrint(s, "时钟周期：%.1f   \r\n", static_cast<float>(static_cast<double>(counter_sum) / test_num));
    shellPrint(s, "测试耗时：%.3f ns\r\n", ns);
    shellPrint(s, "测试耗时：%.6f us\r\n", us);
    shellPrint(s, "等效频率：%.3f MHz\r\n", 1.0f / us);
    shellPrint(s, "等效频率：%.3f kHz\r\n", 1.0f / ms);

    shellPrint(s, "\r\n================== 测试结束 ================== \r\n");


    return 0;
}

#ifdef __cplusplus
}
#endif
