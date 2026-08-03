/**
 * @file    User_DWT.hpp
 * @brief   DWT 周期计数器与硬件断点抽象层。
 * @author  BitWalker
 * @version 2.0.0
 * @date    2026-07-25
 *
 * @note    IsDbgConnected()  是否连接了调试器。
 *          Delay_ns()        延时指定纳秒数。
 *          GetCounter()      获取当前计数器值。
 *          RecordCounter()   记录当前计数器值。
 *          GetDeltaCounter() 获取自上次 RecordCounter() 以来的计数器值。
 *          SetBreakpoint()   设置在不连接调试器时工作的硬件监视点。
 */

#ifndef USER_DWT_HPP
#define USER_DWT_HPP
#ifdef __cplusplus

/* 头文件 ---------------------------------------------------------------- */
#include "stm32h7xx_hal.h"
#include "core_cm7.h"


/* 宏定义 ---------------------------------------------------------------- */
#define BREAKPOINT_FORCE_ENABLE 0  ///< 在连接调试器时使能硬件断点
#define DWT_BREAKPOINT_COUNT 4     ///< DWT 硬件断点数量

///< 获取 Thumb 置位后的函数地址
#define DWT_FUNC_ADDR(f) \
([]{union{decltype(&f) _p;size_t _a;}u={};u._p=(&f);return u._a&~1UL;}())

///< 获取变量地址
#define DWT_VAR_ADDR(var) \
reinterpret_cast<size_t>(&(var))

#ifdef COMP0
#define COMP0_PUSH_SIGN
#pragma push_macro("COMP0")
#undef  COMP0
#endif
#ifdef COMP1
#define COMP1_PUSH_SIGN
#pragma push_macro("COMP1")
#undef  COMP1
#endif
#ifdef COMP2
#define COMP2_PUSH_SIGN
#pragma push_macro("COMP2")
#undef  COMP2
#endif
#ifdef COMP3
#define COMP3_PUSH_SIGN
#pragma push_macro("COMP3")
#undef  COMP3
#endif


/* 公开函数 --------------------------------------------------------------- */
extern "C" {
    void DWT_BreakpointHandle(void);
}


/* 类定义 ---------------------------------------------------------------- */
class User_DWT {
    public:
        User_DWT() noexcept {
            assert_param(is_instance_);
            is_instance_ = false;
        };


        /**
         * @brief 启动 DWT 周期计数器。
         */
        void Start() noexcept {
            // 启用 DEMCR 调试异常和监视器控制寄存器
            CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

            if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) {
                is_dbg_connected_ = true;
                DWT->FUNCTION0 = 0;
                DWT->FUNCTION1 = 0;
                DWT->FUNCTION2 = 0;
                DWT->FUNCTION3 = 0;
            } else {
                // 在未连接调试器时重定向断点到 DebugMon_Handler
                CoreDebug->DEMCR |= CoreDebug_DEMCR_MON_EN_Msk;
            }

            if constexpr (BREAKPOINT_FORCE_ENABLE) {
                CoreDebug->DEMCR |= CoreDebug_DEMCR_MON_EN_Msk;
            }

            // CoreSight 密钥解锁 DWT 访问权限
            DWT->LAR = 0xC5ACCE55;

            // 复位性能计数器
            DWT->CYCCNT  = 0;
            DWT->CPICNT  = 0;
            DWT->LSUCNT  = 0;
            DWT->FOLDCNT = 0;

            // 使能性能计数器
            DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
            DWT->CTRL |= DWT_CTRL_CPIEVTENA_Msk;
            DWT->CTRL |= DWT_CTRL_LSUEVTENA_Msk;
            DWT->CTRL |= DWT_CTRL_FOLDEVTENA_Msk;

            hclk_freq_hz_ = HAL_RCC_GetHCLKFreq();
            assert_param(0 < hclk_freq_hz_);
        };


        ///< 是否连接调试器。
        [[nodiscard]]
        bool IsDbgConnected() const noexcept {
            return is_dbg_connected_;
        };


        /**
        * @brief 至少延时一定地纳秒数，最大 10000 纳秒。
        * @param ns 延时时间，单位：纳秒
        */
        __attribute__((always_inline))
        void Delay_ns(const uint32_t ns) const noexcept {
            const uint32_t start_cnt = DWT->CYCCNT;
            assert_param(ns <= 10000);

            const uint32_t cycles =
                static_cast<uint64_t>(ns) * hclk_freq_hz_ / 1000000000;

            while (DWT->CYCCNT - start_cnt < cycles) {
                __asm__("nop");
            }
        };


        /**
         * @brief 记录当前计数值。
         * @note  与 GetDeltaCounter() 配对使用。
         */
        __attribute__((always_inline))
        void RecordCounter() noexcept {
            last_counter_ = DWT->CYCCNT;
        };


        /**
         * @brief  获取自上次 RecordCounter() 以来的周期增量。
         * @return 计数增量。
         */
        [[nodiscard]] __attribute__((always_inline))
        uint32_t GetDeltaCounter() const noexcept {
            const uint32_t current_counter = DWT->CYCCNT;
            return current_counter - last_counter_;  // 溢出回绕
        };


        ///< 监视点模式。
        enum WatchMode : uint8_t {
            INSTRUCTION = 0x4,
            DATA_READ   = 0x5,
            DATA_WRITE  = 0x6,
            DATA_RW     = 0x7,
        };


        ///< 硬件断点回调函数类型。
        using BP_Cb = void (*)();


        /**
         * @brief 设置硬件监视点。
         * @param addr 监视地址。
         * @param mode 监视点模式。
         * @param func 回调函数，用于处理断点事件。
         * @note  仅在不连接调试器时有效。
         * @return 是否成功设置。
         */
        [[nodiscard]] __attribute__((always_inline))
        bool SetBreakpoint(const size_t    addr,
                           const WatchMode mode,
                           const BP_Cb     func) noexcept {

            if (DWT_BREAKPOINT_COUNT <= used_breakpoints_) {
                return false;
            }

            // NOLINTNEXTLINE
            if (is_dbg_connected_ && !BREAKPOINT_FORCE_ENABLE) {
                // NOLINTNEXTLINE
                return false;
            }

            switch (used_breakpoints_) {
                case 0:
                    DWT->FUNCTION0 = 0;
                    DWT->COMP0 = addr;
                    DWT->MASK0 = 0;
                    DWT->FUNCTION0 = static_cast<uint8_t>(mode);
                    BP0_Callback_ = func;
                    break;
                case 1:
                    DWT->FUNCTION1 = 0;
                    DWT->COMP1 = addr;
                    DWT->MASK1 = 0;
                    DWT->FUNCTION1 = static_cast<uint8_t>(mode);
                    BP1_Callback_ = func;
                    break;
                case 2:
                    DWT->FUNCTION2 = 0;
                    DWT->COMP2 = addr;
                    DWT->MASK2 = 0;
                    DWT->FUNCTION2 = static_cast<uint8_t>(mode);
                    BP2_Callback_ = func;
                    break;
                case 3:
                    DWT->FUNCTION3 = 0;
                    DWT->COMP3 = addr;
                    DWT->MASK3 = 0;
                    DWT->FUNCTION3 = static_cast<uint8_t>(mode);
                    BP3_Callback_ = func;
                    break;
                default: return false;
            }

            used_breakpoints_++;
            return true;
        }

        User_DWT(User_DWT const &)            = delete;
        User_DWT &operator=(User_DWT const &) = delete;
        User_DWT(User_DWT &&)                 = delete;
        User_DWT &operator=(User_DWT &&)      = delete;


        ~User_DWT() = default;


    private:
        ///< 唯一实例标志位。
        static inline bool is_instance_ {true};

        ///< 是否连接调试器。
        bool is_dbg_connected_ {false};

        ///< HCLK 频率，单位：赫兹。
        uint32_t hclk_freq_hz_     {0};
        ///< RecordCounter() 记录的基准计数值。
        uint32_t last_counter_     {0};
        ///< 已经使用的硬件断点数量。
        uint8_t  used_breakpoints_ {0};

        ///< 硬件断点 0 中断回调函数。
        BP_Cb BP0_Callback_ {nullptr};
        ///< 硬件断点 1 中断回调函数。
        BP_Cb BP1_Callback_ {nullptr};
        ///< 硬件断点 2 中断回调函数。
        BP_Cb BP2_Callback_ {nullptr};
        ///< 硬件断点 3 中断回调函数。
        BP_Cb BP3_Callback_ {nullptr};

        friend void DWT_BreakpointHandle();

        __attribute__((always_inline))
        void BreakpointHandle_() const noexcept {
            if ((DWT->FUNCTION0 & DWT_FUNCTION_MATCHED_Msk) != 0) {
                if (BP0_Callback_ != nullptr) {
                    DWT->FUNCTION0 &= ~DWT_FUNCTION_MATCHED_Msk;
                    BP0_Callback_();
                }
            }
            if ((DWT->FUNCTION1 & DWT_FUNCTION_MATCHED_Msk) != 0) {
                if (BP1_Callback_ != nullptr) {
                    DWT->FUNCTION1 &= ~DWT_FUNCTION_MATCHED_Msk;
                    BP1_Callback_();
                }
            }
            if ((DWT->FUNCTION2 & DWT_FUNCTION_MATCHED_Msk) != 0) {
                if (BP2_Callback_ != nullptr) {
                    DWT->FUNCTION2 &= ~DWT_FUNCTION_MATCHED_Msk;
                    BP2_Callback_();
                }
            }
            if ((DWT->FUNCTION3 & DWT_FUNCTION_MATCHED_Msk) != 0) {
                if (BP3_Callback_ != nullptr) {
                    DWT->FUNCTION3 &= ~DWT_FUNCTION_MATCHED_Msk;
                    BP3_Callback_();
                }
            }
        }
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wignored-pragmas"

#ifdef COMP3_PUSH_SIGN
#pragma pop_macro("COMP3")
#endif
#ifdef COMP2_PUSH_SIGN
#pragma pop_macro("COMP2")
#endif
#ifdef COMP1_PUSH_SIGN
#pragma pop_macro("COMP1")
#endif
#ifdef COMP0_PUSH_SIGN
#pragma pop_macro("COMP0")
#endif

#pragma clang diagnostic pop


#endif
#endif //USER_DWT_HPP