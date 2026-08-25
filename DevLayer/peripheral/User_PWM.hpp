/**
 * @file    User_PWM.hpp
 * @brief   PWM 输出抽象层
 * @author  BitWalker
 * @version 1.0.0
 * @date    2026-08-24
 *
 * @note    需调用 Start() 启动 PWM 输出
 *          SetDuty() 设置占空比 范围：0.0 ~ 1.0
 *          SetFrequency() 设置输出频率 单位：Hz
 */


#ifndef USER_PWM_HPP
#define USER_PWM_HPP


/* 头文件 ---------------------------------------------------------------- */
#include "stm32h7xx_hal.h"
#include <cstdint>
#include <vector>

/* 条件编译 --------------------------------------------------------------- */
#ifdef HAL_TIM_MODULE_ENABLED

/* 枚举定义 --------------------------------------------------------------- */
enum class PWM_BIT_WIDTH : uint32_t {
    BIT_WIDTH_16 = 16U,
    BIT_WIDTH_32 = 32U,
};

/* 类定义 ---------------------------------------------------------------- */
class User_PWM {
  public:
    /**
     * @brief  用定时器句柄构造 PWM 输出对象
     * @param  handle    指向 CubeMX 生成的 TIM_HandleTypeDef 的指针
     * @param  channel   定时器 PWM 输出通道
     * @param  bit_width 定时器 PWM 输出通道位宽
     * @note   需在 CubeMX 初始化定时器之后调用
     */
    explicit User_PWM(TIM_HandleTypeDef *handle,
                       uint32_t channel,
                       PWM_BIT_WIDTH bit_width) noexcept;

    /**
     * @brief  启动 PWM 输出，并依据定时器实际配置反推当前频率与占空比
     * @param  tim_clock 定时器所在总线的时钟频率 单位：Hz
     *                   可参考 DevLayer/hardware/tim_freq.h 中的宏定义
     * @return 是否启动成功
     * @note   需在 CubeMX 初始化定时器之后调用
     *         通道已启动时再次调用返回 false
     */
    [[nodiscard]] bool Start(uint32_t tim_clock) noexcept;

    /**
     * @brief  设置 PWM 占空比
     * @param  duty  占空比 范围：0.0 ~ 1.0
     * @return 比较寄存器的值
     */
    [[nodiscard]] uint32_t SetDuty(float duty) const noexcept;

    /**
     * @brief  设置 PWM 输出频率
     * @param  freq  输出频率 单位：Hz
     * @return 自动重载寄存器的值
     * @note   频率变更会影响同定时器其他通道的输出频率
     *         频率变更后需重新设置其他通道的 PWM 占空比
     */
    [[nodiscard]] uint32_t SetFrequency(uint32_t freq) const noexcept;

    /**
     * @brief  获取当前输出频率
     * @return 输出频率 单位：Hz
     */
    [[nodiscard]] uint32_t GetFrequency() const noexcept;

    /**
     * @brief  获取当前占空比
     * @return 占空比 范围：0.0 ~ 1.0
     */
    [[nodiscard]] float GetDuty() const noexcept;


    User_PWM(User_PWM const &)            = delete;
    User_PWM &operator=(User_PWM const &) = delete;
    User_PWM(User_PWM &&)                 = delete;
    User_PWM &operator=(User_PWM &&)      = delete;


    ~User_PWM() = default;


  private:
    TIM_HandleTypeDef *handle_;       ///< TIM HAL 句柄指针
    uint32_t           channel_;      ///< PWM 输出通道
    PWM_BIT_WIDTH      bit_width_;    ///< PWM 输出通道位宽
    uint32_t           tim_clock_{};    ///< 定时器总线时钟频率 单位：Hz


    class PWM_Drive {
    public:
        uint32_t channel;    ///< PWM 输出通道
        float duty;          ///< PWM 占空比
    };

    class TIM_Drive {
    public:
        TIM_HandleTypeDef *handle;            ///< TIM HAL 句柄指针
        std::vector<PWM_Drive> pwm_drives;    ///< PWM 输出通道信息
    };

    /**
     * @brief  获取所有已构造的 PWM 输出对象的定时器信息
     * @return 定时器信息的引用
     */
    static std::vector<TIM_Drive>& Get_TIM_Drives() noexcept;

};


#endif /* HAL_TIM_MODULE_ENABLED */
#endif /* USER_PWM_HPP */
