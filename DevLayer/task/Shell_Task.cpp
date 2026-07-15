#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "bsp_register.h"
#include "../shell/shell_port.h"


extern "C" {
[[noreturn]]
    void Start_Latter_Shell(void *argument) {
        ShellPort_Init();

        while (true) {
            shellTask(&shell);
            osDelay(pdMS_TO_TICKS(50));
        }
    }
}
