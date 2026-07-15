#include "main.h"
#include "bsp_register.h"


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
User_COMP comp_2(&hcomp2);
#endif


#ifdef HCRC_ENABLED
// NOLINTNEXTLINE
User_CRC hardware_crc(&hcrc);
#endif





extern "C" {
    void bsp_Init() {

    }
}