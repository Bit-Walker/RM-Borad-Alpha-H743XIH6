#ifndef BSP_REGISTER_H
#define BSP_REGISTER_H
#include "bsp_hal_handle.h"

#include "peripheral/User_DWT.hpp"
extern User_DWT dwt;

#ifdef HAL_IWDG_MODULE_ENABLED
#include "peripheral/User_IWDG.hpp"
#ifdef HIWDG1_ENABLED
extern User_IWDG iwdg;
#endif
#endif


#ifdef HAL_GPIO_MODULE_ENABLED
#include "display/User_LED.hpp"
extern User_LED state_led;
#endif


#ifdef HAL_COMP_MODULE_ENABLED
#include "peripheral/User_COMP.hpp"
#ifdef HCOMP1_ENABLED
extern User_COMP comp_1;
#endif
#ifdef HCOMP2_ENABLED
extern User_COMP comp_2;
#endif
#endif


#ifdef HAL_CRC_MODULE_ENABLED
#include "peripheral/User_CRC.hpp"
#ifdef HCRC_ENABLED
extern User_CRC hardware_crc;
#endif
#endif


#ifdef HAL_RNG_MODULE_ENABLED
#include "peripheral/User_RNG.hpp"
#ifdef HRNG_ENABLED
extern User_RNG hardware_rng;
#endif
#endif


#ifdef HAL_TIM_MODULE_ENABLED
#include "peripheral/User_PWM.hpp"
#ifdef HTIM2_ENABLED
extern User_PWM tim2_ch1_pwm;
extern User_PWM tim2_ch2_pwm;
extern User_PWM tim2_ch3_pwm;
extern User_PWM tim2_ch4_pwm;
#endif
#ifdef HTIM5_ENABLED
extern User_PWM tim5_ch1_pwm;
extern User_PWM tim5_ch2_pwm;
extern User_PWM tim5_ch3_pwm;
extern User_PWM tim5_ch4_pwm;
#endif
#endif


#endif //BSP_REGISTER_H