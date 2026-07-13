/**
 * @file    user_iwdg.hpp
 * @brief   独立看门狗抽象层。
 * @author  BitWalker
 * @version 1.0.0
 * @date    2026-07-14
 *
 * @note    需显式调用 Start() 启动计数器。
 *          需在独立高优先级任务中周期性调用 Refresh() 以防系统复位。
 */


#ifndef USER_IWDG_HPP
#define USER_IWDG_HPP


/* 头文件 ---------------------------------------------------------------- */
#include "stm32h7xx_hal.h"
#include <cstdint>


/* 类定义 ---------------------------------------------------------------- */
class User_iwdg {
  public:
    /**
     * @brief  用 IWDG 句柄构造对象。
     * @param  handle  指向 CubeMX 生成的 IWDG_HandleTypeDef 的指针。
     */
    explicit User_iwdg(const IWDG_HandleTypeDef *handle) noexcept;

    /**
     * @brief  启动 IWDG 递减计数器。
     */
    void Start() const noexcept;

    /**
     * @brief  重装载 IWDG 计数器。
     * @note   必须在超时周期内周期性调用，否则触发系统复位。
     */
    void Refresh() const noexcept;

    /// @brief 获取当前预分频器配置值。
    [[nodiscard]] std::uint32_t GetPrescaler() const noexcept;

    /// @brief 获取当前重装载配置值。
    [[nodiscard]] std::uint32_t GetReload() const noexcept;

    /// @brief 获取当前窗口配置值。
    [[nodiscard]] std::uint32_t GetWindow() const noexcept;

    /// @brief 获取超时时间。单位：ms
    [[nodiscard]] std::uint32_t GetTimeoutMs() const noexcept;

    /// @brief 获取窗口关闭时间。Window 禁用时返回 0。单位：ms
    [[nodiscard]] std::uint32_t GetWindowMs() const noexcept;

    /// @brief 获取推荐的喂狗周期。单位：ms
    [[nodiscard]] std::uint32_t GetRefreshPeriodMs() const noexcept;


    User_iwdg(User_iwdg const &)            = delete;
    User_iwdg &operator=(User_iwdg const &) = delete;
    User_iwdg(User_iwdg &&)                 = delete;
    User_iwdg &operator=(User_iwdg &&)      = delete;


    ~User_iwdg() = default;


  private:
    IWDG_HandleTypeDef handle_;  ///< IWDG HAL 句柄。
};


#endif /* USER_IWDG_HPP */
