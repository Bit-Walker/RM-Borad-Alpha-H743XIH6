#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "bsp_register.h"

#ifdef HAL_IWDG_MODULE_ENABLED
extern "C" {
[[noreturn]]
    void Start_IWDG_Refresh(void *argument) {
        iwdg.Start();
        while (true) {
            iwdg.Refresh();
            osDelay(pdMS_TO_TICKS(iwdg.GetRefreshPeriodMs()));
        }
    }
}
#endif
