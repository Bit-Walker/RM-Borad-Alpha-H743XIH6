/**
 * @file    User_DWT.hpp
 * @brief   DWT 周期计数器抽象层。
 * @author  BitWalker
 * @version 1.0.0
 * @date    2026-07-25
 *
 * @note    Start() 启动计数器。
 *          Clear() 复位计数器。
 *          GetCounter() 获取当前计数器值。
 *          RecordCounter() 记录当前计数器值。
 *          GetDeltaCounter() 获取自上次 RecordCounter() 以来的计数器值。
 */

#ifndef USER_DWT_HPP
#define USER_DWT_HPP


/* 头文件 ---------------------------------------------------------------- */
#include "memory/memory_seg.h"
#include "stm32h7xx_hal.h"
#include "core_cm7.h"
#include <cstdint>


/* 类定义 ---------------------------------------------------------------- */
class User_DWT {
    public:
        explicit User_DWT() noexcept = delete;


        /**
         * @brief 启动 DWT 周期计数器。
         */
        static void Start() noexcept {
            // 启用 DEMCR 调试异常和监视器控制寄存器
            CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
            // CoreSight 密钥解锁 DWT 访问权限
            DWT->LAR = 0xC5ACCE55;
            // 清除 CYCCNT 计数器
            DWT->CYCCNT = 0;
            // 使能 CYCCNT 计数器
            DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
        };


        /**
         * @brief 复位 CYCCNT 计数器。
         */
        static void Clear() noexcept {
            DWT->CYCCNT = 0;
        };


        /// @brief 读取当前 DWT 周期计数器的值。
        [[nodiscard]] __attribute__((always_inline))
        static std::uint32_t GetCounter() noexcept {
            return DWT->CYCCNT;
        };


        /**
         * @brief 记录当前计数值。
         * @note  与 GetDeltaCounter() 配对使用。
         */
        __attribute__((always_inline))
        static void RecordCounter() noexcept {
            last_counter_ = DWT->CYCCNT;
        };


        /**
         * @brief  获取自上次 RecordCounter() 以来的周期增量。
         * @return 计数增量。
         */
        [[nodiscard]] __attribute__((always_inline))
        static std::uint32_t GetDeltaCounter() noexcept {
            return DWT->CYCCNT - last_counter_;
        };


        User_DWT(User_DWT const &)            = delete;
        User_DWT &operator=(User_DWT const &) = delete;
        User_DWT(User_DWT &&)                 = delete;
        User_DWT &operator=(User_DWT &&)      = delete;


        ~User_DWT() = delete;


    private:
        ///< RecordCounter() 记录的基准计数值。
        inline static DTCMRAM std::uint32_t last_counter_ = 0;
};


#endif //USER_DWT_HPP
