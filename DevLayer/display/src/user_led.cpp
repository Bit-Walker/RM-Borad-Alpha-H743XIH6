#include "../user_led.hpp"

User_led::User_led(GPIO_TypeDef* port, const uint16_t pin)
    : port_(port), pin_(pin) {
}

void User_led::On() const {
    HAL_GPIO_WritePin(port_, pin_, GPIO_PIN_SET);
}

void User_led::Off() const {
    HAL_GPIO_WritePin(port_, pin_, GPIO_PIN_RESET);
}

void User_led::Toggle() const {
    HAL_GPIO_TogglePin(port_, pin_);
}
