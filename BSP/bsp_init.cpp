#include "main.h"
#include "bsp_register.h"
#include "transport/user_rtt.h"
#include "peripheral/User_DWT.hpp"


User_DWT dwt;

#ifdef HIWDG1_ENABLED
// NOLINTNEXTLINE
User_IWDG iwdg(&hiwdg1);
#endif


#ifdef HAL_GPIO_MODULE_ENABLED
User_LED state_led(State_LED_GPIO_Port, State_LED_Pin);
#endif


#ifdef HCOMP1_ENABLED
// NOLINTNEXTLINE
User_COMP comp_1(&hcomp1);
#endif
#ifdef HCOMP2_ENABLED
// NOLINTNEXTLINE
User_COMP comp_2(&hcomp2);
#endif


#ifdef HCRC_ENABLED
// NOLINTNEXTLINE
User_CRC hardware_crc(&hcrc);
#endif


#ifdef HRNG_ENABLED
// NOLINTNEXTLINE
User_RNG hardware_rng(&hrng);
#endif

#ifdef HTIM2_ENABLED
#ifdef HTIM2_ENABLED
// NOLINTNEXTLINE
User_PWM tim2_ch1_pwm(&htim2, TIM_CHANNEL_1, PWM_BIT_WIDTH::BIT_WIDTH_32);
// NOLINTNEXTLINE
User_PWM tim2_ch2_pwm(&htim2, TIM_CHANNEL_2, PWM_BIT_WIDTH::BIT_WIDTH_32);
// NOLINTNEXTLINE
User_PWM tim2_ch3_pwm(&htim2, TIM_CHANNEL_3, PWM_BIT_WIDTH::BIT_WIDTH_32);
// NOLINTNEXTLINE
User_PWM tim2_ch4_pwm(&htim2, TIM_CHANNEL_4, PWM_BIT_WIDTH::BIT_WIDTH_32);
#endif
#ifdef HTIM5_ENABLED
// NOLINTNEXTLINE
User_PWM tim5_ch1_pwm(&htim5, TIM_CHANNEL_1, PWM_BIT_WIDTH::BIT_WIDTH_32);
// NOLINTNEXTLINE
User_PWM tim5_ch2_pwm(&htim5, TIM_CHANNEL_2, PWM_BIT_WIDTH::BIT_WIDTH_32);
// NOLINTNEXTLINE
User_PWM tim5_ch3_pwm(&htim5, TIM_CHANNEL_3, PWM_BIT_WIDTH::BIT_WIDTH_32);
// NOLINTNEXTLINE
User_PWM tim5_ch4_pwm(&htim5, TIM_CHANNEL_4, PWM_BIT_WIDTH::BIT_WIDTH_32);
#endif
#endif


extern "C" {
    void BSP_Init() {
        JScope_Init();
        iwdg.Start();
        dwt.Start();


#ifdef DEBUG
        __HAL_DBGMCU_FREEZE_WWDG1();

        __HAL_DBGMCU_FREEZE_TIM2();
        __HAL_DBGMCU_FREEZE_TIM3();
        __HAL_DBGMCU_FREEZE_TIM4();
        __HAL_DBGMCU_FREEZE_TIM5();
        __HAL_DBGMCU_FREEZE_TIM6();
        __HAL_DBGMCU_FREEZE_TIM7();
        __HAL_DBGMCU_FREEZE_TIM12();
        __HAL_DBGMCU_FREEZE_TIM13();
        __HAL_DBGMCU_FREEZE_TIM14();
        __HAL_DBGMCU_FREEZE_LPTIM1();
        __HAL_DBGMCU_FREEZE_I2C1();
        __HAL_DBGMCU_FREEZE_I2C2();
        __HAL_DBGMCU_FREEZE_I2C3();

        __HAL_DBGMCU_FREEZE_FDCAN();

        __HAL_DBGMCU_FREEZE_TIM1();
        __HAL_DBGMCU_FREEZE_TIM8();
        __HAL_DBGMCU_FREEZE_TIM15();
        __HAL_DBGMCU_FREEZE_TIM16();
        __HAL_DBGMCU_FREEZE_TIM17();
        __HAL_DBGMCU_FREEZE_HRTIM();

        __HAL_DBGMCU_FREEZE_I2C4();
        __HAL_DBGMCU_FREEZE_LPTIM2();
        __HAL_DBGMCU_FREEZE_LPTIM3();
        __HAL_DBGMCU_FREEZE_LPTIM4();
        __HAL_DBGMCU_FREEZE_LPTIM5();
        __HAL_DBGMCU_FREEZE_RTC();
        __HAL_DBGMCU_FREEZE_IWDG1();
#endif
    }
}