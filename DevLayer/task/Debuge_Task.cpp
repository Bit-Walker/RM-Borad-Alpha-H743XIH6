#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "bsp_register.h"
#include "transport/user_rtt.h"
#include "../shell/shell_port.h"


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
        while (true) {
            state_led.Toggle();
            osDelay(pdMS_TO_TICKS(1000));
        }
    }
}
#endif


#ifdef HAL_COMP_MODULE_ENABLED
extern "C" {
    void COMP_Callback(User_COMP const *comp, void *argument) {
        const auto led = static_cast<User_LED *>(argument);
        led->Set(comp->GetOutputLevel());
    }
[[noreturn]]
    void Test_COMP(void) {
        if (!comp_1.Start(COMP_Callback, &state_led)) {
            Error_Handler();
        }
        while (true) {
            osDelay(pdMS_TO_TICKS(100));
        }
    }
}
#endif


extern "C" {
    void Start_Debug_Task(void *argument) {
        Test_Template();
    }
}