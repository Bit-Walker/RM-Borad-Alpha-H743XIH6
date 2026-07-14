#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "interface/user_segger_rtt.h"
#include "peripheral/user_iwdg.hpp"
#include "display/user_led.hpp"
#include "peripheral/user_comp.hpp"


extern "C" {
[[noreturn]]
    void Test_Template(void) {

        while (true) {

            osDelay(pdMS_TO_TICKS(1000));
        }
    }
}


extern "C" {
[[noreturn]]
    void Test_RTT(void) {
        while (true) {
            uint8_t x = 0;
            if (RTT_Scanf(0, "%u", &x) > 0) {
                RTT_Printf(0, "Hello %u \n", x);
            }
            osDelay(pdMS_TO_TICKS(100));
        }
    }
}


#ifdef HAL_GPIO_MODULE_ENABLED
extern "C" {
[[noreturn]]
    void Test_LED(void) {
        static User_led led(State_LED_GPIO_Port, State_LED_Pin);
        while (true) {
            led.Toggle();
            osDelay(pdMS_TO_TICKS(1000));
        }
    }
}
#endif


#ifdef HAL_COMP_MODULE_ENABLED
extern "C" {
    void COMP_Callback(User_comp const *comp, void *argument) {
        const auto led = static_cast<User_led *>(argument);
        led->Set(comp->GetOutputLevel());
    }
[[noreturn]]
    void Test_COMP(void) {
        static User_led led(State_LED_GPIO_Port, State_LED_Pin);
        static User_comp comp(&hcomp1, COMP_Callback, &led);
        comp.Start();
        while (true) {

            osDelay(pdMS_TO_TICKS(1000));
        }
    }
}
#endif


extern "C" {
    void Start_Debug_Task(void *argument) {
        Test_Template();
    }
}