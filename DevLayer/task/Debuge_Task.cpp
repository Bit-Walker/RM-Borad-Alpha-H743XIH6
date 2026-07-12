#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "../interface/user_segger_rtt.h"

extern "C" {
    void Test_RTT(void) {
        uint8_t x = 0;
        if (RTT_Scanf(0, "%u", &x) > 0) {
            RTT_Printf(0, "Hello %u \n", x);
        }
    }
}

extern "C" {
[[noreturn]]
    void Start_Debug_Task(void *argument) {
        while (true)
        {
            osDelay(100);

            Test_RTT();
        }
    }
}