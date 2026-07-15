/**
 * @file    user_crc.hpp
 * @brief   硬件 CRC 计算抽象层。
 * @author  BitWalker
 * @version 1.0.0
 * @date    2026-07-15
 *
 * @note    Calculate() 为单次计算，Accumulate() 支持分块累加。
 */


#ifndef USER_CRC_HPP
#define USER_CRC_HPP


/* 头文件 ---------------------------------------------------------------- */
#include "stm32h7xx_hal.h"
#include <cstdint>

/* 条件编译 --------------------------------------------------------------- */
#ifdef HAL_CRC_MODULE_ENABLED


/* 类定义 ---------------------------------------------------------------- */
class User_crc {
  public:
    /**
     * @brief  用 CRC 句柄构造对象。
     * @param  handle  指向 CubeMX 生成的 CRC_HandleTypeDef 的指针。
     */
    explicit User_crc(const CRC_HandleTypeDef *handle) noexcept;

    /**
     * @brief  单次计算 CRC。
     * @param  pBuffer  数据缓冲区指针。
     * @param  length   数据长度（单位由 InputDataFormat 决定）。
     * @return  CRC 计算结果。
     */
    [[nodiscard]] std::uint32_t Calculate(std::uint32_t pBuffer[],
                                          std::uint32_t length) noexcept;

    /**
     * @brief  分块计算 CRC。
     * @param  pBuffer  数据缓冲区指针。
     * @param  length   数据长度（单位由 InputDataFormat 决定）。
     * @return  当前累加的 CRC 结果。
     */
    [[nodiscard]] std::uint32_t Accumulate(std::uint32_t pBuffer[],
                                           std::uint32_t length) noexcept;

    /**
     * @brief  重置 CRC 数据寄存器。
     */
    void Reset() const noexcept;

    /**
     * @brief  设置 CRC 初始值。
     * @param  value  32 位初始值。
     */
    void SetInitValue(std::uint32_t value) const noexcept;

    /// @brief 获取当前多项式。
    [[nodiscard]] std::uint32_t GetPolynomial() const noexcept;

    /// @brief 获取 CRC 位宽。
    [[nodiscard]] std::uint32_t GetCRCLength() const noexcept;

    /// @brief 获取 CRC 初始值。
    [[nodiscard]] std::uint32_t GetInitValue() const noexcept;


    User_crc(User_crc const &)            = delete;
    User_crc &operator=(User_crc const &) = delete;
    User_crc(User_crc &&)                 = delete;
    User_crc &operator=(User_crc &&)      = delete;


    ~User_crc() = default;


  private:
    CRC_HandleTypeDef handle_;  ///< CRC HAL 句柄。
};


#endif /* HAL_CRC_MODULE_ENABLED */
#endif /* USER_CRC_HPP */
