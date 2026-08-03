/* 头文件 ---------------------------------------------------------------- */
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "peripheral/User_RNG.hpp"


/* 条件编译 --------------------------------------------------------------- */
#ifdef HAL_RNG_MODULE_ENABLED

/* 宏定义 ---------------------------------------------------------------- */
#define USER_RNG_MAX_INSTANCES   1U  ///< 最大 RNG 实例数。

/* 命名空间 --------------------------------------------------------------- */
namespace {
    User_RNG *rng_instances[USER_RNG_MAX_INSTANCES] = {};
    uint32_t  rng_count = 0;
}


/* 中断分发 --------------------------------------------------------------- */
/// @brief 覆写 HAL 数据准备回调，分派到对应的 User_RNG 实例。
// NOLINTNEXTLINE
extern "C" void HAL_RNG_ReadyDataCallback(RNG_HandleTypeDef *const hrng,
                                          uint32_t const           random32bit) {

    for (uint32_t i = 0; i < rng_count; i++) {
        if (auto *const self = rng_instances[i]) {
            if (self->handle_->Instance == hrng->Instance) {
                self->OnDataReady(random32bit);
                break;
            }
        }
    }
}


/* 构造函数 --------------------------------------------------------------- */
User_RNG::User_RNG(RNG_HandleTypeDef *const handle) noexcept
    : handle_(handle) {

    assert_param(handle != nullptr);
    assert_param(rng_count < USER_RNG_MAX_INSTANCES);

    for (uint32_t i = 0; i < rng_count; i++) {
        assert_param(rng_instances[i]->handle_->Instance != handle->Instance);
    }

    rng_instances[rng_count++] = this;
}


/* 成员方法 --------------------------------------------------------------- */
bool User_RNG::GetRandFloat(float_t *random,
                            const float_t max,
                            const float_t min) noexcept {

    assert_param(random != nullptr);
    assert_param(max > min);

    if (random == nullptr) {
        return false;
    }

    if (!ready_) {
        if (HAL_RNG_GetState(handle_) == HAL_RNG_STATE_BUSY) {
            auto const tickstart = HAL_GetTick();
            while (HAL_RNG_GetState(handle_) == HAL_RNG_STATE_BUSY) {
                osDelay(pdMS_TO_TICKS(1));
                if (HAL_GetTick() - tickstart > HAL_RNG_ERROR_TIMEOUT) {
                    // 超时通常意味着没有在 CubeMX 中开启中断
                    assert_param(false);
                }
            }
        } else {
            if (HAL_RNG_GenerateRandomNumber(handle_, &random_) != HAL_OK) {
                return false;
            }
        }
    }

    *random = static_cast<float_t>(random_) / static_cast<float_t>(UINT32_MAX) * (max - min) + min;
    ready_ = false;

    if (HAL_RNG_GenerateRandomNumber_IT(handle_) != HAL_OK) {
        return false;
    }

    return true;
}

/* 私有方法 --------------------------------------------------------------- */
void User_RNG::OnDataReady(uint32_t const random) noexcept {
    random_ = random;
    ready_  = true;
}


#endif /* HAL_RNG_MODULE_ENABLED */
