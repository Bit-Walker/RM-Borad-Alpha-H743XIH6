/* 头文件 ---------------------------------------------------------------- */
#include "peripheral/user_iwdg.hpp"


/* 构造函数 --------------------------------------------------------------- */
User_iwdg::User_iwdg(const IWDG_HandleTypeDef *const handle) noexcept
    : handle_(*handle) {

    assert_param(handle != nullptr);
}


/* 成员方法 --------------------------------------------------------------- */
void User_iwdg::Start() const noexcept {
    __HAL_IWDG_START(&handle_);
}


void User_iwdg::Refresh() const noexcept {
    __HAL_IWDG_RELOAD_COUNTER(&handle_);
}


std::uint32_t User_iwdg::GetPrescaler() const noexcept {
    return handle_.Init.Prescaler;
}


std::uint32_t User_iwdg::GetReload() const noexcept {
    return handle_.Init.Reload;
}


std::uint32_t User_iwdg::GetWindow() const noexcept {
    return handle_.Init.Window;
}


std::uint32_t User_iwdg::GetTimeoutMs() const noexcept {
    auto const prescaler = handle_.Init.Prescaler;
    auto const reload    = handle_.Init.Reload;
    auto const divider   = 4u << prescaler;

    return (divider * (reload + 1) * 1000u) / LSI_VALUE;
}


std::uint32_t User_iwdg::GetWindowMs() const noexcept {
    auto const window = handle_.Init.Window;

    if (window == IWDG_WINDOW_DISABLE) {
        return 0;
    }

    auto const prescaler = handle_.Init.Prescaler;
    auto const reload    = handle_.Init.Reload;
    auto const divider   = 4u << prescaler;

    return (divider * (reload - window + 1) * 1000u) / LSI_VALUE;
}


std::uint32_t User_iwdg::GetRefreshPeriodMs() const noexcept {
    auto const timeout_ms = GetTimeoutMs();

    if (handle_.Init.Window == IWDG_WINDOW_DISABLE) {
        return timeout_ms / 4u;
    }

    auto const window_ms = GetWindowMs();
    return (timeout_ms + window_ms) / 2u;
}
