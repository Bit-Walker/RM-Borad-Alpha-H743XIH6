#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "../peripheral/user_iwdg.hpp"


extern "C" {
[[noreturn]]
    void Start_IWDG_Refresh(void *argument) {
        static User_iwdg iwdg(&hiwdg1);

        iwdg.Start();

        while (true) {
            iwdg.Refresh();
            osDelay(pdMS_TO_TICKS(iwdg.GetRefreshPeriodMs()));
        }
    }
}
