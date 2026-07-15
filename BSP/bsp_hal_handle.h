#ifndef BSP_HAL_HANDLE_H
#define BSP_HAL_HANDLE_H
#include "main.h"

#define HDMA_LPUART1_RX_ENABLED
extern DMA_HandleTypeDef hdma_lpuart1_rx;

#define HDMA_LPUART1_TX_ENABLED
extern DMA_HandleTypeDef hdma_lpuart1_tx;

#define HIWDG1_ENABLED
extern IWDG_HandleTypeDef hiwdg1;

#define HLPUART1_ENABLED
extern UART_HandleTypeDef hlpuart1;

#endif //BSP_HAL_HANDLE_H
