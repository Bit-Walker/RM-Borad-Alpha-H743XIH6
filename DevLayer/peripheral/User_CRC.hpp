/**
 * @file    User_CRC.hpp
 * @brief   硬件 CRC 计算抽象层。
 * @author  BitWalker
 * @version 1.5.0
 * @date    2026-07-15
 *
 * @note    Calculate() 进行单次计算。
 *          Accumulate() 支持分块累加。
 */


#ifndef USER_CRC_HPP
#define USER_CRC_HPP


/* 头文件 ---------------------------------------------------------------- */
#include "stm32h7xx_hal.h"
#include <cstdint>

/* 条件编译 --------------------------------------------------------------- */
#ifdef HAL_CRC_MODULE_ENABLED


/* 类定义 ---------------------------------------------------------------- */
class User_CRC {
  public:
    /**
     * @brief  用 CRC 句柄构造对象。
     * @param  handle  指向 CubeMX 生成的 CRC_HandleTypeDef 的指针。
     */
    explicit User_CRC(CRC_HandleTypeDef *handle) noexcept;

    /**
     * @brief  单次计算 CRC。
     * @param  pBuffer  数据缓冲区指针。
     * @param  length   数据长度，单位由 InputDataFormat 决定。
     * @return  CRC 计算结果。
     */
    [[nodiscard]] uint32_t Calculate(uint32_t const pBuffer[],
                                     uint32_t length) const noexcept;

    /**
     * @brief  分块计算 CRC。
     * @param  pBuffer  数据缓冲区指针。
     * @param  length   数据长度，单位由 InputDataFormat 决定。
     * @return  当前累加的 CRC 结果。
     */
    [[nodiscard]] uint32_t Accumulate(uint32_t const pBuffer[],
                                      uint32_t length) const noexcept;


    User_CRC(User_CRC const &)            = delete;
    User_CRC &operator=(User_CRC const &) = delete;
    User_CRC(User_CRC &&)                 = delete;
    User_CRC &operator=(User_CRC &&)      = delete;


    ~User_CRC() = default;


  private:
    CRC_HandleTypeDef *handle_;  ///< CRC HAL 句柄指针。
};


#endif /* HAL_CRC_MODULE_ENABLED */
#endif /* USER_CRC_HPP */
