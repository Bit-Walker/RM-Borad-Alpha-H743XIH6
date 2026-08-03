/* 头文件 ---------------------------------------------------------------- */
#include "peripheral/User_COMP.hpp"

/* 条件编译 --------------------------------------------------------------- */
#ifdef HAL_COMP_MODULE_ENABLED


/* 中断分发 --------------------------------------------------------------- */
/// @brief 覆写 HAL 回调，分派到对应的 User_comp 实例。
// NOLINTNEXTLINE
extern "C" void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp) {
    for (uint32_t i = 0; i < User_COMP::comp_count_; i++) {
        if (const auto *const self = User_COMP::comp_instances_[i]) {
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
    assert_param(comp_count_ < USER_COMP_MAX_INSTANCES);

    for (uint32_t i = 0; i < comp_count_; i++) {
        assert_param(comp_instances_[i]->handle_->Instance != handle->Instance);
    }

    comp_instances_[comp_count_++] = this;
}


/* 成员方法 --------------------------------------------------------------- */
bool User_COMP::Start(Callback const cb, void *const arg) noexcept {
    if (cb != nullptr) {
        callback_     = cb;
        callback_arg_ = arg;
    }

    HAL_StatusTypeDef status = HAL_OK;

    if (callback_) {
        if ((status = HAL_COMP_Start_IT(handle_)) == HAL_OK) {
            return true;
        }
    } else {
        if ((status = HAL_COMP_Start(handle_)) == HAL_OK) {
            return true;
        }
    }

    assert_param(status == HAL_OK);
    return false;
}


bool User_COMP::Stop() const noexcept {
    HAL_StatusTypeDef status = HAL_OK;

    if (callback_) {
        if ((status = HAL_COMP_Stop_IT(handle_)) == HAL_OK) {
            return true;
        }
    } else {
        if ((status = HAL_COMP_Stop(handle_)) == HAL_OK) {
            return true;
        }
    }

    assert_param(status == HAL_OK);
    return false;
}


bool User_COMP::GetOutputLevel() const noexcept {
    return (HAL_COMP_GetOutputLevel(handle_) != COMP_OUTPUT_LEVEL_LOW);
}


void User_COMP::SetCallbackArg(void *const arg) noexcept {
    assert_param(callback_ != nullptr);

    callback_arg_ = arg;
}


void User_COMP::OnTrigger() const noexcept {
    if (callback_) {
        callback_(this, callback_arg_);
    }
}


#endif /* HAL_COMP_MODULE_ENABLED */
