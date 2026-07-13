/**
 * @file    user_led.hpp
 * @brief   GPIO 驱动的用户 LED 抽象层。
 *
 * @warning 本类不保证对同一 GPIO 引脚的并发访问时的线程安全。
 */

#ifndef USER_LED_HPP_
#define USER_LED_HPP_

#include "stm32h7xx_hal.h"
#include <cstdint>

class User_led {
  public:
    /**
     * @brief  构造一个经过校验的 User_led 句柄。
     * @param  port         GPIO  端口基地址。
     * @param  pin          GPIO  引脚位掩码。
     * @param  is_reversal  true  表示 LED 为低电平有效。
     *                      false 表示 LED 为高电平有效。
     */
    explicit User_led(GPIO_TypeDef *port, std::uint16_t pin,
                      bool is_reversal = false) noexcept;

    virtual ~User_led() = default;

    User_led(User_led const &)            = delete;
    User_led &operator=(User_led const &) = delete;
    User_led(User_led &&)                 = delete;
    User_led &operator=(User_led &&)      = delete;

    /**
     * @brief  读取 LED 的状态。
     * @return true 表示点亮，false 表示熄灭。
     */
    [[nodiscard]] bool Get() const noexcept;

    /**
     * @brief  设置 LED 的状态。
     * @param  state  true = 点亮，false = 熄灭。
     */
    void Set(bool state) const noexcept;

    /// @brief 点亮 LED。
    void On() const noexcept;

    /// @brief 熄灭 LED。
    void Off() const noexcept;

    /// @brief 翻转 LED 的状态。
    void Toggle() const noexcept;


  private:
    GPIO_TypeDef *const port_;         // GPIO 端口基地址。
    std::uint16_t const pin_;          // GPIO 引脚位掩码。
    bool const          is_reversal_;  // true  = 低电平有效。
                                       // false = 高电平有效。
};

#endif /* USER_LED_HPP_ */
