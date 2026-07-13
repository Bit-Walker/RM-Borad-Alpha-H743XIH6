#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"

#include "../interface/user_segger_rtt.h"

extern "C" {
    void peripherals_init(void) {
        JScope_Init();
    }
}