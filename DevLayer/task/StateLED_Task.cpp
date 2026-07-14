#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "display/user_led.hpp"

#define STATE_LED_TASK_ENABLED

#ifdef HAL_GPIO_MODULE_ENABLED
#ifdef STATE_LED_TASK_ENABLED
extern "C" {
[[noreturn]]
    void Start_StateLED_Toggle(void *argument) {
        static User_led led(State_LED_GPIO_Port, State_LED_Pin);
        while (true) {
            led.Toggle();
            osDelay(pdMS_TO_TICKS(1000));
        }
    }
}
#endif
#endif
