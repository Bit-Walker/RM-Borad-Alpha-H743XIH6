/**
 * @file    cmd_clk.cpp
 * @brief   打印 hardware 层定义的各时钟频率
 * @note    时钟值均取自 hardware/clk_freq.h 与 hardware/tim_freq.h 中的宏
 * @author  BitWalker
 * @version 1.0.0
 * @date    2026-08-25
 *
 */

#include "../shell_port.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_rcc_ex.h"
#include "hardware/clk_freq.h"
#include "hardware/tim_freq.h"


#ifdef __cplusplus
extern "C" {
#endif


/* 静态函数 ------------------------------------------------------------ */

/**
 * @brief  打印单个时钟频率，大于 1 MHz 以 MHz 显示，否则以 kHz 显示
 */
static void printFreq(Shell *s, const char *name, uint32_t hz)
{
    if (hz >= 1000000UL) {
        shellPrint(s, "  %-12s : %9.3f MHz\r\n", name, hz / 1000000.0);
    }else {
        shellPrint(s, "  %-12s : %9.3f kHz\r\n", name, hz / 1000.0);
    }
}


/* 函数 --------------------------------------------------------------- */

int shellClk(int argc, char *argv[])
{
    Shell *s = shellGetCurrent();
    if (!s) return -1;

    shellPrint(s, "\r\n================== 时钟树 ==================\r\n\r\n");

    /* ---- 系统时钟 ---------------------------------------------------- */

    shellPrint(s, "系统时钟:\r\n");
    printFreq(s, "SYS_CLK", SYS_CLK);
    printFreq(s, "HCLK_CLK", HCLK_CLK);

    /* ---- APB 总线 ---------------------------------------------------- */

    shellPrint(s, "\r\nAPB 时钟:\r\n");
    printFreq(s, "APB1_CLK", APB1_CLK);
    printFreq(s, "APB2_CLK", APB2_CLK);
    printFreq(s, "APB3_CLK", APB3_CLK);
    printFreq(s, "APB4_CLK", APB4_CLK);

    /* ---- 定时器总线时钟 ---------------------------------------------- */

    shellPrint(s, "\r\n定时器时钟:\r\n");
    printFreq(s, "APB1_TIM_CLK", APB1_TIM_CLK);
    printFreq(s, "APB2_TIM_CLK", APB2_TIM_CLK);
    printFreq(s, "APB3_TIM_CLK", APB3_TIM_CLK);
    printFreq(s, "APB4_TIM_CLK", APB4_TIM_CLK);

    /* ---- 各定时器 --------------------------------------- */

    shellPrint(s, "\r\nAPB1 定时器 (D2 Domain):\r\n");
    printFreq(s, "TIM2_CLK", TIM2_CLK);
    printFreq(s, "TIM3_CLK", TIM3_CLK);
    printFreq(s, "TIM4_CLK", TIM4_CLK);
    printFreq(s, "TIM5_CLK", TIM5_CLK);
    printFreq(s, "TIM6_CLK", TIM6_CLK);
    printFreq(s, "TIM7_CLK", TIM7_CLK);
    printFreq(s, "TIM12_CLK", TIM12_CLK);
    printFreq(s, "TIM13_CLK", TIM13_CLK);
    printFreq(s, "TIM14_CLK", TIM14_CLK);
    printFreq(s, "LPTIM1_CLK", LPTIM1_CLK);

    shellPrint(s, "\r\nAPB2 定时器 (D2 Domain):\r\n");
    printFreq(s, "TIM1_CLK", TIM1_CLK);
    printFreq(s, "TIM8_CLK", TIM8_CLK);
    printFreq(s, "TIM15_CLK", TIM15_CLK);
    printFreq(s, "TIM16_CLK", TIM16_CLK);
    printFreq(s, "TIM17_CLK", TIM17_CLK);
    printFreq(s, "HRTIM1_CLK", HRTIM1_CLK);

    shellPrint(s, "\r\nAPB3 定时器 (D1 Domain):\r\n");
    printFreq(s, "LPTIM2_CLK", LPTIM2_CLK);
    printFreq(s, "LPTIM3_CLK", LPTIM3_CLK);
    printFreq(s, "LPTIM4_CLK", LPTIM4_CLK);
    printFreq(s, "LPTIM5_CLK", LPTIM5_CLK);

    shellPrint(s, "\r\n===========================================\r\n");

    return 0;
}

#ifdef __cplusplus
}
#endif
