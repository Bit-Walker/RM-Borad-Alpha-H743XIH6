/* 头文件 ---------------------------------------------------------------- */
#include "peripheral/User_COMP.hpp"

/* 条件编译 --------------------------------------------------------------- */
#ifdef HAL_COMP_MODULE_ENABLED

/* 宏定义 ---------------------------------------------------------------- */
#define USER_COMP_MAX_INSTANCES 2U

/* 命名空间 --------------------------------------------------------------- */
namespace {
    User_COMP    *comp_instances[USER_COMP_MAX_INSTANCES] = {};
    std::uint32_t comp_count = 0;
}


/* 中断分发 --------------------------------------------------------------- */
/// @brief 覆写 HAL 弱回调，分派到对应的 User_comp 实例。
extern "C" void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp) {
    for (std::uint32_t i = 0; i < comp_count; i++) {
        if (const auto *const self = comp_instances[i]) {
            if (self->handle_->Instance == hcomp->Instance) {
                self->OnTrigger();
                break;
            }
        }
    }
}


/* 构造函数 --------------------------------------------------------------- */
User_COMP::User_COMP(COMP_HandleTypeDef *const handle) noexcept
    : handle_(handle) {

    assert_param(handle != nullptr);
    assert_param(comp_count < USER_COMP_MAX_INSTANCES);

    for (std::uint32_t i = 0; i < comp_count; i++) {
        assert_param(comp_instances[i]->handle_->Instance != handle->Instance);
    }

    comp_instances[comp_count++] = this;
}


/* 成员方法 --------------------------------------------------------------- */
bool User_COMP::Start(Callback const cb, void *const arg) noexcept {
    if (cb != nullptr) {
        callback_     = cb;
        callback_arg_ = arg;
    }

    if (callback_) {
        return (HAL_COMP_Start_IT(handle_) == HAL_OK);
    }

    return (HAL_COMP_Start(handle_) == HAL_OK);
}


bool User_COMP::Stop() const noexcept {
    if (callback_) {
        return (HAL_COMP_Stop_IT(handle_) == HAL_OK);
    }

    return (HAL_COMP_Stop(handle_) == HAL_OK);
}


bool User_COMP::GetOutputLevel() const noexcept {
    return (HAL_COMP_GetOutputLevel(handle_) != COMP_OUTPUT_LEVEL_LOW);
}


void User_COMP::SetCallbackArg(void *const arg) noexcept {
    assert_param(callback_ != nullptr);

    callback_arg_ = arg;
}


std::uint32_t User_COMP::GetMode() const noexcept {
    return handle_->Init.Mode;
}


std::uint32_t User_COMP::GetNonInvertingInput() const noexcept {
    return handle_->Init.NonInvertingInput;
}


std::uint32_t User_COMP::GetInvertingInput() const noexcept {
    return handle_->Init.InvertingInput;
}


void User_COMP::OnTrigger() const noexcept {
    if (callback_) {
        callback_(this, callback_arg_);
    }
}


#endif /* HAL_COMP_MODULE_ENABLED */
