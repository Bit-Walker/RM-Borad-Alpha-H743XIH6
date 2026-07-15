/* 头文件 ---------------------------------------------------------------- */
#include "display/User_LED.hpp"

/* 条件编译 --------------------------------------------------------------- */
#ifdef HAL_GPIO_MODULE_ENABLED


/* 构造函数 --------------------------------------------------------------- */
User_LED::User_LED(GPIO_TypeDef *const port,
                   std::uint16_t const pin,
                   bool const          is_reversal) noexcept
    : port_(port), pin_(pin), is_reversal_(is_reversal) {

    assert_param((port_ == GPIOA) || (port_ == GPIOB) || (port_ == GPIOC) ||
                 (port_ == GPIOD) || (port_ == GPIOE) || (port_ == GPIOF) ||
                 (port_ == GPIOG) || (port_ == GPIOH) || (port_ == GPIOI) ||
                 (port_ == GPIOJ) || (port_ == GPIOK));

    assert_param(IS_GPIO_PIN(pin_));
}


/* 成员方法 --------------------------------------------------------------- */
bool User_LED::Get() const noexcept {
    bool const pin_high = (HAL_GPIO_ReadPin(port_, pin_) == GPIO_PIN_SET);
    return is_reversal_ ? !pin_high : pin_high;
}


void User_LED::Set(bool const state) const noexcept {
    state ? On() : Off();
}


void User_LED::On() const noexcept {
    HAL_GPIO_WritePin(port_, pin_,
                      is_reversal_ ? GPIO_PIN_RESET : GPIO_PIN_SET);
}


void User_LED::Off() const noexcept {
    HAL_GPIO_WritePin(port_, pin_,
                      is_reversal_ ? GPIO_PIN_SET : GPIO_PIN_RESET);
}


void User_LED::Toggle() const noexcept {
    HAL_GPIO_TogglePin(port_, pin_);
}


#endif /* HAL_GPIO_MODULE_ENABLED */