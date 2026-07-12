/* 头文件 ---------------------------------------------------------------- */
#include "../user_segger_rtt.h"
#include <string.h>
#include <stdio.h>

/* 全局变量 --------------------------------------------------------------- */
JScope_Transmit_t jscope_transmit = {0};
uint8_t JScope_RTT_UpBuffer[BUFFER_SIZE_UP] = {0};


/* 全局函数 --------------------------------------------------------------- */

/**
 * @brief 初始化 JScope 传输模块
 * @note  配置 RTT 上行缓冲区用于 JScope 数据传输
 */
void JScope_Init() {
    SEGGER_RTT_Init();
    SEGGER_RTT_ConfigUpBuffer(JSCOPE_BUFFER_INDEX, JSCOPE_BUFFER_NAME, &JScope_RTT_UpBuffer[0], BUFFER_SIZE_UP, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
}


/**
 * @brief 发送 JScope 数据
 * @note  通过 RTT 将数据发送到 JScope，通常将这个函数放在定时器中断回调，定时发送数据
 */
void JScope_Transmit(const uint32_t delta_time) {
    jscope_transmit.timestamp += delta_time;
    SEGGER_RTT_Write(JSCOPE_BUFFER_INDEX, &jscope_transmit, sizeof(jscope_transmit));
}


/**
* @brief RTT 格式化输出
* @param index   RTT 使用的缓冲区索引
* @param format  格式化字符串
* @param ...     可变参数
*/
void RTT_Printf(const uint8_t index, const char * format, ...) {
    static char buffer[PRINTF_BUFFER_SIZE];
    va_list args;

    va_start(args, format);
    const int len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if (len > 0 && len < sizeof(buffer)) {
        SEGGER_RTT_Write(index, buffer, len);
    }
}



/**
* @brief RTT 格式化输入
* @param index   RTT 使用的缓冲区索引
* @param format  格式化字符串
* @param ...     可变参数
* @return 成功解析的参数数量，失败返回 -1
*/
int32_t RTT_Scanf(const uint8_t index, const char *format, ...) {
    static uint8_t buffer[PRINTF_BUFFER_SIZE];
    const uint16_t len = SEGGER_RTT_Read(index, buffer, sizeof(buffer));

    if (len == 0)
        return -1;

    buffer[len] = '\0';  // 确保字符串结束

    va_list args;
    va_start(args, format);
    const int32_t result = vsscanf((const char*)buffer, format, args);
    va_end(args);

    return result;
}