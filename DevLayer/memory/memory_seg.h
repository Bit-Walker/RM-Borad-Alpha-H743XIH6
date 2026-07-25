#ifndef MEMORY_SEGMENTATION_H
#define MEMORY_SEGMENTATION_H


/* 定义内存分段 ----------------------------------------------------------------*/

/**
 * @brief ITCM 紧密耦合指令段
 * @note  可存储数据，可存储指令，无缓存
 * 不支持 BDMA，DMA1，DMA2
 * 仅支持 MDMA
 */
#define ITCMRAM __attribute__((section(".itcmram")))

/**
 * @brief DTCM 紧密耦合数据段
 * @note  可存储数据，无缓存
 * 不支持 BDMA，DMA1，DMA2
 * 仅支持 MDMA
 */
#define DTCMRAM __attribute__((section(".dtcmram")))

/**
 * @brief RAM_D1 时钟域数据段，也是变量默认的存储位置
 * @note  可存储数据，启用缓存
 * 下属 AXI SRAM
 * 不支持 BDMA
 * 仅支持 MDMA，DMA1，DMA2
 */
#define RAM_D1  __attribute__((section(".data")))

/**
 * @brief RAM_D2 时钟域数据段
 * @note  可存储数据，可存储指令，禁用缓存
 * 下属 SRAM1，SRAM2，SRAM3
 * 不支持 BDMA
 * 仅支持 MDMA，DMA1，DMA2
 */
#define RAM_D2  __attribute__((section(".ram_d2")))

/**
 * @brief RAM_D3 时钟域数据段
 * @note  可存储数据，禁用缓存
 * 下属 SRAM4
 * 支持 BDMA，MDMA，DMA1，DMA2
 */
#define RAM_D3  __attribute__((section(".ram_d3")))


#endif //MEMORY_SEGMENTATION_H
