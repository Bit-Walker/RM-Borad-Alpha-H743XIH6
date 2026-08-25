#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "bsp_register.h"
#include "transport/user_rtt.h"
#include "../shell/shell_port.h"


extern "C" {
[[noreturn]]
    void Test_Template(void) {
        while (true) {
            osDelay(pdMS_TO_TICKS(1000));
        }
    }
}


extern "C" {
[[noreturn]]
    void Test_RTT(void) {
        while (true) {
            uint8_t x = 0;
            if (RTT_Scanf(0, "%u", &x) > 0) {
                RTT_Printf(0, "Hello %u \n", x);
            }
            osDelay(pdMS_TO_TICKS(100));
        }
    }
}


#ifdef HAL_GPIO_MODULE_ENABLED
extern "C" {
[[noreturn]]
    void Test_LED(void) {
        while (true) {
            state_led.Toggle();
            osDelay(pdMS_TO_TICKS(1000));
        }
    }
}
#endif


#ifdef HAL_COMP_MODULE_ENABLED
extern "C" {
    void COMP_Callback(User_COMP const *comp, void *argument) {
        const auto led = static_cast<User_LED *>(argument);
        led->Set(comp->GetOutputLevel());
    }
[[noreturn]]
    void Test_COMP(void) {
        if (!comp_1.Start(COMP_Callback, &state_led)) {
            assert_param(false);
        }
        while (true) {
            osDelay(pdMS_TO_TICKS(100));
        }
    }
}
#endif


#ifdef HAL_RNG_MODULE_ENABLED
extern "C" {
[[noreturn]]
    void Test_RNG(void) {
        while (true) {
            osDelay(pdMS_TO_TICKS(1000));
            float random = 0.0f;
            if (hardware_rng.GetRandFloat(&random,10,1)) {
                RTT_Printf(0, "%f ", random);
            }
        }
    }
}
#endif


#ifdef HAL_CRC_MODULE_ENABLED
extern "C" {
[[noreturn]]
    void Test_RNG(void) {
        while (true) {
            osDelay(pdMS_TO_TICKS(1000));
            constexpr uint8_t random[3] = {0x01, 0x02, 0x03};
            RTT_Printf(0, "%u ", hardware_crc.Calculate(random, sizeof(random)));
        }
    }
}
#endif


#ifdef HAL_TIM_MODULE_ENABLED
extern "C" {
#include "hardware/tim_freq.h"
[[noreturn]]
    void Test_PWM(void) {
    assert_param(tim2_ch1_pwm.Start(TIM2_CLK));

    (void)tim2_ch1_pwm.SetFrequency(1000);
    (void)tim2_ch1_pwm.SetDuty(0.5);

    while (true) {
        osDelay(pdMS_TO_TICKS(1));
        const float duty_wave = (sin(static_cast<float>(HAL_GetTick()) / 1000.0f) + 1.0f) / 2.0f;
        (void)tim2_ch1_pwm.SetDuty(duty_wave);
        const float freq_wave = (sin(static_cast<float>(HAL_GetTick()) / 100.0f ) + 1.0f) / 2.0f * 9000.0f + 1000.0f;
        (void)tim2_ch1_pwm.SetFrequency(static_cast<uint32_t>(freq_wave));

    }
}
}
#endif


extern "C" {
    void Start_Debug_Task(void *argument) {
        Test_Template();
    }
}