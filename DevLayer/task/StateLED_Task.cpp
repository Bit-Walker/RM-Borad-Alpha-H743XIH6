#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "display/user_led.hpp"

extern "C" {

[[noreturn]]
    void Start_StateLED_Toggle(void *argument) {
        static User_led led(State_LED_GPIO_Port, State_LED_Pin);

        while (true)
        {
            osDelay(1000);
            led.Toggle();
        }
    }

}
