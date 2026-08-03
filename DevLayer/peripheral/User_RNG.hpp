/**
 * @file    User_RNG.hpp
 * @brief   硬件真随机数生成器抽象层。
 * @author  BitWalker
 * @version 1.1.0
 * @date    2026-07-21
 *
 * @note    Generate() 生成一个 32 位随机数。
 */


#ifndef USER_RNG_HPP
#define USER_RNG_HPP


/* 头文件 ---------------------------------------------------------------- */
#include "stm32h7xx_hal.h"


/* 条件编译 --------------------------------------------------------------- */
#ifdef HAL_RNG_MODULE_ENABLED


/* 类定义 ---------------------------------------------------------------- */
class User_RNG {
  public:
    /**
     * @brief  用 RNG 句柄构造对象。
     * @param  handle  指向 CubeMX 生成的 RNG_HandleTypeDef 的指针。
     */
    explicit User_RNG(RNG_HandleTypeDef *handle) noexcept;


    /**
     * @brief 获取指定范围内的随机浮点数。
     * @param random  输出随机值。
     * @param max     可取到的最大值。
     * @param min     可取到的最小值。
     * @return 是否获取成功。
     */
    [[nodiscard]] bool GetRandFloat(float_t *random,
                                    float_t max = 1.0f,
                                    float_t min = 0.0f) noexcept;


    User_RNG(User_RNG const &)            = delete;
    User_RNG &operator=(User_RNG const &) = delete;
    User_RNG(User_RNG &&)                 = delete;
    User_RNG &operator=(User_RNG &&)      = delete;


    ~User_RNG() = default;


  private:
    RNG_HandleTypeDef *handle_;         ///< RNG HAL 句柄指针。
    uint32_t           random_ = 0;     ///< 缓存的随机数。
    bool               ready_ = false;  ///< 数据就绪标志位。


    /// @brief HAL 数据就绪回调分发到本实例。
    void OnDataReady(uint32_t random) noexcept;
    friend void HAL_RNG_ReadyDataCallback(RNG_HandleTypeDef *hrng,
                                          uint32_t           random32bit);
};


#endif /* HAL_RNG_MODULE_ENABLED */
#endif /* USER_RNG_HPP */
