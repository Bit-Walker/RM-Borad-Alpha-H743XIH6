#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "bsp_register.h"

#define STATE_LED_TASK_ENABLED

#ifdef HAL_GPIO_MODULE_ENABLED
#ifdef STATE_LED_TASK_ENABLED
extern "C" {
[[noreturn]]
    void Start_StateLED_Toggle(void *argument) {
        while (true) {
            state_led.Toggle();
            osDelay(pdMS_TO_TICKS(1000));
        }
    }
}
#endif
#endif
