/* 头文件 ---------------------------------------------------------------- */
#include "peripheral/User_PWM.hpp"


/* 条件编译 --------------------------------------------------------------- */
#ifdef HAL_TIM_MODULE_ENABLED

/* 构造函数 --------------------------------------------------------------- */
User_PWM::User_PWM(TIM_HandleTypeDef *const handle,
                   const uint32_t           channel,
                   const PWM_BIT_WIDTH      bit_width) noexcept
    : handle_(handle), channel_(channel), bit_width_(bit_width) {

    assert_param(handle != nullptr);
    assert_param(IS_TIM_CHANNELS(channel));
    assert_param(bit_width == PWM_BIT_WIDTH::BIT_WIDTH_16
              || bit_width == PWM_BIT_WIDTH::BIT_WIDTH_32);

    // NOLINTNEXTLINE
    for (auto &tim_drive : Get_TIM_Drives()) { if (tim_drive.handle == handle) {
            tim_drive.pwm_drives.push_back({channel, 0.0F});
            return;
        }
    }

    Get_TIM_Drives().push_back({handle, {{channel, 0.0F}}});

}


/* 成员方法 --------------------------------------------------------------- */
bool User_PWM::Start(const uint32_t tim_clock) noexcept {
    assert_param(tim_clock > 0);
    tim_clock_ = tim_clock;
    return HAL_TIM_PWM_Start(handle_, channel_) == HAL_OK;
}


uint32_t User_PWM::SetDuty(const float duty) const noexcept {

    assert_param(duty >= 0.0F);
    assert_param(duty <= 1.0F);

    const auto compare_reg = static_cast<uint32_t>(
        static_cast<float>(__HAL_TIM_GET_AUTORELOAD(handle_) + 1U) * duty);

    __HAL_TIM_SET_COMPARE(handle_, channel_, compare_reg);

    // NOLINTNEXTLINE
    for (auto &tim_drive : Get_TIM_Drives()) { if (tim_drive.handle == handle_) {
            // NOLINTNEXTLINE
            for (auto &pwm_drive : tim_drive.pwm_drives) { if (pwm_drive.channel == channel_) {
                    pwm_drive.duty = duty;
                }
            }
        }
    }

    return compare_reg;
}


uint32_t User_PWM::SetFrequency(const uint32_t freq) const noexcept {
    const uint32_t clock = tim_clock_ / (handle_->Init.Prescaler + 1U);

    assert_param(freq > 0);
    assert_param(freq <= clock);

    uint32_t prescaler_reg = 0;
    uint32_t reload_reg = 0;

    const uint32_t max_value = (bit_width_ == PWM_BIT_WIDTH::BIT_WIDTH_16) ?
                                65535 : 4294967295;

    for (prescaler_reg = 0; prescaler_reg <= max_value; prescaler_reg++) {
        reload_reg = static_cast<uint32_t>(ceilf(static_cast<float>(tim_clock_) /
                static_cast<float>(freq * (prescaler_reg + 1)))) - 1;

        if (reload_reg <= max_value) {
            break;
        }
    }

    if (reload_reg > max_value) {
        return 0;
    }

    __HAL_TIM_SET_PRESCALER(handle_, prescaler_reg);
    __HAL_TIM_SET_AUTORELOAD(handle_, reload_reg);

    // NOLINTNEXTLINE
    for (auto &tim_drive : Get_TIM_Drives()) { if (tim_drive.handle == handle_) {
            // NOLINTNEXTLINE
            for (auto &pwm_drive : tim_drive.pwm_drives) {
                const auto compare_reg = static_cast<uint32_t>(
                static_cast<float>(__HAL_TIM_GET_AUTORELOAD(tim_drive.handle) + 1U) * pwm_drive.duty);

                __HAL_TIM_SET_COMPARE(tim_drive.handle, pwm_drive.channel, compare_reg);
            }
        }
    }

    return reload_reg;
}

uint32_t User_PWM::GetFrequency() const noexcept {
    const uint32_t clock = tim_clock_ / (handle_->Init.Prescaler + 1U);
    const uint32_t period = __HAL_TIM_GET_AUTORELOAD(handle_) + 1U;
    const uint32_t freq = clock / period;

    return freq;
}

float User_PWM::GetDuty() const noexcept {
    const uint32_t period = __HAL_TIM_GET_AUTORELOAD(handle_) + 1U;
    const uint32_t compare_reg = __HAL_TIM_GET_COMPARE(handle_, channel_);
    const float duty = static_cast<float>(compare_reg) /
            static_cast<float>(period);

    return duty;
}

/* 私有方法 --------------------------------------------------------------- */
std::vector<User_PWM::TIM_Drive>& User_PWM::Get_TIM_Drives() noexcept {
    static std::vector<TIM_Drive> tim_drives;
    return tim_drives;
}


#endif /* HAL_TIM_MODULE_ENABLED */