#include "../shell_port.h"
#include "SEGGER_RTT.h"


/* 全局变量 --------------------------------------------------------------- */
Shell  shell;
char   shell_buffer[512];


/* 覆写回调函数 ------------------------------------------------------------ */
static signed short shellWriteRtt(char *data, unsigned short len)
{
    return (signed short)SEGGER_RTT_Write(0, data, (unsigned)len);
}

static signed short shellReadRtt(char *data, unsigned short len)
{
    const unsigned int n = SEGGER_RTT_Read(0, data, (unsigned)len);
    return (signed short)n;
}


/* 全局函数 --------------------------------------------------------------- */
void ShellPort_Init(void)
{
    shell.write = shellWriteRtt;
    shell.read  = shellReadRtt;

    shellInit(&shell, shell_buffer, sizeof(shell_buffer));
}
