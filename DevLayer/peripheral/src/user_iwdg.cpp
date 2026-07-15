/* 头文件 ---------------------------------------------------------------- */
#include "peripheral/user_iwdg.hpp"

/* 条件编译 --------------------------------------------------------------- */
#ifdef HAL_IWDG_MODULE_ENABLED

/* 宏定义 ---------------------------------------------------------------- */
#define USER_IWDG_REFRESH_MARGIN 4U  ///< 无窗口看门狗的刷新时间与超时时间比。


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
    std::uint32_t period_ms;

    if (handle_.Init.Window == IWDG_WINDOW_DISABLE) {
        period_ms = timeout_ms / USER_IWDG_REFRESH_MARGIN;
    } else {
        auto const window_ms = GetWindowMs();
        period_ms = (timeout_ms + window_ms) / 2u;
    }

    return (period_ms < 1u) ? 1u : period_ms;
}


#endif /* HAL_IWDG_MODULE_ENABLED */
