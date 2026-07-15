/**
 * @file    shell_port.h
 * @brief   letter-shell 移植层头文件
 * @note    使用 SEGGER RTT channel 0 作为传输层
 * @author  BitWalker
 * @version 1.0.0
 * @date    2026-07-13
 *
 */

#ifndef SHELL_PORT_H
#define SHELL_PORT_H

#ifdef __cplusplus
extern "C" {
#endif


/* 头文件 ---------------------------------------------------------------- */
#include "../../Library/letter-shell/shell.h"


/* 全局变量 --------------------------------------------------------------- */

extern Shell shell;
extern char shell_buffer[512];


/* 全局函数 --------------------------------------------------------------- */

/**
 * @brief  初始化 letter-shell
 * @note   需在 FreeRTOS 任务中调用
 */
void ShellPort_Init(void);


#ifdef __cplusplus
}
#endif

#endif /* SHELL_PORT_H */
