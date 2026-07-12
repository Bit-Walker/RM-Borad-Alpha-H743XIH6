#ifndef USER_SEGGER_RTT_H
#define USER_SEGGER_RTT_H
#ifdef __cplusplus
extern "C" {
#endif


/* 头文件 ---------------------------------------------------------------- */
#include "SEGGER_RTT/SEGGER_RTT.h"
#include "SEGGER_RTT/SEGGER_RTT_Conf.h"


/* 宏定义 ---------------------------------------------------------------- */
#define JSCOPE_BUFFER_INDEX     1                   // JScope 使用的 RTT 缓冲区索引
#define JSCOPE_BUFFER_NAME      "JScope_T4F4F4F4"   // JScope 缓冲区名称
#define PRINTF_BUFFER_SIZE      256                 // Printf 缓冲区大小


/* 结构体 ---------------------------------------------------------------- */
#pragma pack(push, 1)
typedef struct {
    uint32_t timestamp;  /* 时间戳 单位：us */
    float val_1;
    float val_2;
    float val_3;
} JScope_Transmit_t;
#pragma pack(pop)


/* 全局变量 --------------------------------------------------------------- */
extern JScope_Transmit_t jscope_transmit;
extern uint8_t JScope_RTT_UpBuffer[BUFFER_SIZE_UP];


/* 全局函数 --------------------------------------------------------------- */
void JScope_Init();
void JScope_Transmit(uint32_t delta_time);

void RTT_Printf(uint8_t index, const char * format, ...);
int32_t RTT_Scanf(uint8_t index, const char *format, ...);


#ifdef __cplusplus
}
#endif
#endif