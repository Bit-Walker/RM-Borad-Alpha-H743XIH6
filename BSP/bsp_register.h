#ifndef BSP_REGISTER_H
#define BSP_REGISTER_H
#include "bsp_hal_handle.h"


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



#endif //BSP_REGISTER_H
