/**
 * @file    user_comp.hpp
 * @brief   模拟比较器抽象层。
 * @author  BitWalker
 * @version 1.0.0
 * @date    2026-07-14
 *
 * @note    需调用 Start() 启动比较器。
 *          GetOutputLevel() 读取输出电平。
 */


#ifndef USER_COMP_HPP
#define USER_COMP_HPP


/* 头文件 ---------------------------------------------------------------- */
#include "stm32h7xx_hal.h"
#include <cstdint>

/* 条件编译 --------------------------------------------------------------- */
#ifdef HAL_COMP_MODULE_ENABLED


/* 类定义 ---------------------------------------------------------------- */
class User_comp {
  public:
    /// @brief 中断触发回调函数类型。arg 为 SetCallback() 传入的用户参数。
    using Callback = void (*)(User_comp const *, void *arg);

    /**
     * @brief  用 COMP 句柄构造对象。
     * @param  handle  指向 CubeMX 生成的 COMP_HandleTypeDef 的指针。
     * @param  cb      中断触发回调。默认 nullptr 为轮询模式，非空则采用中断模式。
     * @param  arg     回调时透传的用户参数。
     */
    explicit User_comp(const COMP_HandleTypeDef *handle,
                       Callback cb  = nullptr,
                       void    *arg = nullptr) noexcept;

    /**
     * @brief  启动比较器。
     * @note   若构造时传入了回调则自动以中断模式启动，
     *         否则以轮询模式启动。
     */
    void Start() noexcept;

    /**
     * @brief  停止比较器。
     */
    void Stop() noexcept;

    /**
     * @brief  读取比较器输出电平。
     * @return true  同相输入端电压高于反相输入端。
     * @return false 同相输入端电压低于反相输入端。
     * @note   受 OutputPol 极性配置影响。
     */
    [[nodiscard]] bool GetOutputLevel() const noexcept;

    /**
     * @brief  设置回调函数的用户参数。
     * @param  arg  回调时透传的用户参数。
     */
    void SetCallbackArg(void *arg) noexcept;

    /// @brief 获取功耗模式。
    [[nodiscard]] std::uint32_t GetMode() const noexcept;

    /// @brief 获取同相输入端配置。
    [[nodiscard]] std::uint32_t GetNonInvertingInput() const noexcept;

    /// @brief 获取反相输入端配置。
    [[nodiscard]] std::uint32_t GetInvertingInput() const noexcept;


    User_comp(User_comp const &)            = delete;
    User_comp &operator=(User_comp const &) = delete;
    User_comp(User_comp &&)                 = delete;
    User_comp &operator=(User_comp &&)      = delete;


    ~User_comp() = default;


  private:
    COMP_HandleTypeDef handle_;                    ///< COMP HAL 句柄。
    Callback           callback_     = nullptr;    ///< 中断触发回调。
    void              *callback_arg_ = nullptr;    ///< 中断触发回调透传的用户参数。

    /// @brief 由 HAL 回调分发的内部触发处理。
    void OnTrigger() const noexcept;
    friend void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp);
};


#endif /* HAL_COMP_MODULE_ENABLED */
#endif /* USER_COMP_HPP */
