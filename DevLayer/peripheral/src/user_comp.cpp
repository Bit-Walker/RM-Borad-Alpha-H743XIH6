/* 头文件 ---------------------------------------------------------------- */
#include "peripheral/user_comp.hpp"

/* 条件编译 --------------------------------------------------------------- */
#ifdef HAL_COMP_MODULE_ENABLED

/* 宏定义 ---------------------------------------------------------------- */
#define USER_COMP_MAX_INSTANCES 2U

/* 命名空间 --------------------------------------------------------------- */
namespace {
    User_comp    *comp_instances[USER_COMP_MAX_INSTANCES] = {};
    std::uint32_t comp_count = 0;
}


/* 中断分发 --------------------------------------------------------------- */
/// @brief 覆写 HAL 弱回调，分派到对应的 User_comp 实例。
extern "C" void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp) {
    for (std::uint32_t i = 0; i < comp_count; i++) {
        if (const auto *const self = comp_instances[i]) {
            if (self->handle_.Instance == hcomp->Instance) {
                self->OnTrigger();
                break;
            }
        }
    }
}


/* 构造函数 --------------------------------------------------------------- */
User_comp::User_comp(const COMP_HandleTypeDef *const handle,
                     Callback const cb,
                     void *const    arg) noexcept
    : handle_(*handle),
      callback_(cb),
      callback_arg_(arg) {

    assert_param(handle != nullptr);
    assert_param(comp_count < USER_COMP_MAX_INSTANCES);

    for (std::uint32_t i = 0; i < comp_count; i++) {
        assert_param(comp_instances[i]->handle_.Instance != handle->Instance);
    }

    comp_instances[comp_count++] = this;
}


/* 成员方法 --------------------------------------------------------------- */
void User_comp::Start() noexcept {
    if (callback_) {
        HAL_COMP_Start_IT(&handle_);
    } else {
        __HAL_COMP_ENABLE(&handle_);
    }
}


void User_comp::Stop() noexcept {
    if (callback_) {
        HAL_COMP_Stop_IT(&handle_);
    } else {
        __HAL_COMP_DISABLE(&handle_);
    }
}


bool User_comp::GetOutputLevel() const noexcept {
    return (HAL_COMP_GetOutputLevel(&handle_) != COMP_OUTPUT_LEVEL_LOW);
}


void User_comp::SetCallbackArg(void *const arg) noexcept {
    assert_param(callback_ != nullptr);
    callback_arg_ = arg;
}


std::uint32_t User_comp::GetMode() const noexcept {
    return handle_.Init.Mode;
}


std::uint32_t User_comp::GetNonInvertingInput() const noexcept {
    return handle_.Init.NonInvertingInput;
}


std::uint32_t User_comp::GetInvertingInput() const noexcept {
    return handle_.Init.InvertingInput;
}


void User_comp::OnTrigger() const noexcept {
    if (callback_) {
        callback_(this, callback_arg_);
    }
}


#endif /* HAL_COMP_MODULE_ENABLED */
