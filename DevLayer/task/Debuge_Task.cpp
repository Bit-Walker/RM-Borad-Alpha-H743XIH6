#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "bsp_register.h"
#include "interface/user_segger_rtt.h"


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


extern "C" {
[[noreturn]]
    void Test_Shell(void) {
        ShellPort_Init();

        while (true) {
            shellTask(&shell);
            osDelay(pdMS_TO_TICKS(10));
        }
    }
}


#ifdef HAL_GPIO_MODULE_ENABLED
extern "C" {
[[noreturn]]
    void Test_LED(void) {
        while (true) {
            state_led.Toggle();
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