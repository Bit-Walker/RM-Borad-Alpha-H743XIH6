#include "main.h"
#include "bsp_register.h"
#include "bsp_hal_handle.h"


User_led state_led(State_LED_GPIO_Port, State_LED_Pin);
// NOLINTNEXTLINE
User_iwdg iwdg(&hiwdg1);


extern "C" {
    void bsp_Init() {

    }
}