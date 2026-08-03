/* 头文件 ---------------------------------------------------------------- */
#include "peripheral/User_DWT.hpp"
#include "bsp_register.h"


/* 公开函数 --------------------------------------------------------------- */
extern "C" void DWT_BreakpointHandle(void) {
    dwt.BreakpointHandle_();
}
