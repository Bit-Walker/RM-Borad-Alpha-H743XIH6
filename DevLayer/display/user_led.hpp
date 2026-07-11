#ifndef USER_LED_H_
#define USER_LED_H_

#include "stm32h7xx_hal.h"

class User_led {
public:
    User_led(GPIO_TypeDef* port, uint16_t pin);
    virtual ~User_led() = default;

    void On() const;
    void Off() const;
    void Toggle() const;

private:
    GPIO_TypeDef* port_;
    uint16_t pin_;
};

#endif /* USER_LED_H_ */