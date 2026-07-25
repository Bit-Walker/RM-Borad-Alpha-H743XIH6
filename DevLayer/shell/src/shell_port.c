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
    unsigned int n = SEGGER_RTT_Read(0, data, (unsigned)len);

    static uint8_t last_char_is_ff = 0;

    if (n == len) {
        if (last_char_is_ff && data[0] =='\x0b') {
            n = 0;
        }

        if (data[0] =='\xff') {
            last_char_is_ff = 1;
            n = 0;
        } else {
            last_char_is_ff = 0;
        }
    }

    return (signed short)n;
}


/* 全局函数 --------------------------------------------------------------- */
void ShellPort_Init(void)
{
    shell.write = shellWriteRtt;
    shell.read  = shellReadRtt;

    shellInit(&shell, shell_buffer, sizeof(shell_buffer));
}
