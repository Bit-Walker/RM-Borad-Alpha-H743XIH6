/* 头文件 ---------------------------------------------------------------- */
#include "peripheral/User_IWDG.hpp"

/* 条件编译 --------------------------------------------------------------- */
#ifdef HAL_IWDG_MODULE_ENABLED

/* 宏定义 ---------------------------------------------------------------- */
#define USER_IWDG_REFRESH_MARGIN 4U  ///< 无窗口看门狗的刷新时间与超时时间比。


/* 构造函数 --------------------------------------------------------------- */
User_IWDG::User_IWDG(IWDG_HandleTypeDef *const handle) noexcept
    : handle_(handle) {

    assert_param(handle != nullptr);
}


/* 成员方法 --------------------------------------------------------------- */
void User_IWDG::Start() const noexcept {
    __HAL_IWDG_START(handle_);
}


bool User_IWDG::Refresh() const noexcept {
    return (HAL_IWDG_Refresh(handle_) == HAL_OK);
}


std::uint32_t User_IWDG::GetPrescaler() const noexcept {
    return handle_->Init.Prescaler;
}


std::uint32_t User_IWDG::GetReload() const noexcept {
    return handle_->Init.Reload;
}


std::uint32_t User_IWDG::GetWindow() const noexcept {
    return handle_->Init.Window;
}


std::uint32_t User_IWDG::GetTimeoutMs() const noexcept {
    auto const prescaler = handle_->Init.Prescaler;
    auto const reload    = handle_->Init.Reload;
    auto const divider   = 4u << prescaler;

    return (divider * (reload + 1) * 1000u) / LSI_VALUE;
}


std::uint32_t User_IWDG::GetWindowMs() const noexcept {
    auto const window = handle_->Init.Window;

    if (window == IWDG_WINDOW_DISABLE) {
        return 0;
    }

    auto const prescaler = handle_->Init.Prescaler;
    auto const reload    = handle_->Init.Reload;
    auto const divider   = 4u << prescaler;

    return (divider * (reload - window + 1) * 1000u) / LSI_VALUE;
}


std::uint32_t User_IWDG::GetRefreshPeriodMs() const noexcept {
    auto const timeout_ms = GetTimeoutMs();
    std::uint32_t period_ms;

    if (handle_->Init.Window == IWDG_WINDOW_DISABLE) {
        period_ms = timeout_ms / USER_IWDG_REFRESH_MARGIN;
    } else {
        auto const window_ms = GetWindowMs();
        period_ms = (timeout_ms + window_ms) / 2u;
    }

    return (period_ms < 1u) ? 1u : period_ms;
}


#endif /* HAL_IWDG_MODULE_ENABLED */
