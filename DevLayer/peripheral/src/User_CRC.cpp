/* 头文件 ---------------------------------------------------------------- */
#include "peripheral/User_CRC.hpp"

/* 条件编译 --------------------------------------------------------------- */
#ifdef HAL_CRC_MODULE_ENABLED


/* 构造函数 --------------------------------------------------------------- */
User_CRC::User_CRC(CRC_HandleTypeDef *handle) noexcept
    : handle_(handle) {

    assert_param(handle != nullptr);
}


/* 成员方法 --------------------------------------------------------------- */
uint32_t User_CRC::Calculate(uint32_t const pBuffer[],
                             uint32_t const length) const noexcept {

    assert_param(pBuffer != nullptr);
    assert_param(length > 0);

    return HAL_CRC_Calculate(handle_, pBuffer, length);
}


uint32_t User_CRC::Accumulate(uint32_t const pBuffer[],
                              uint32_t const length) const noexcept {

    assert_param(pBuffer != nullptr);
    assert_param(length > 0);

    return HAL_CRC_Accumulate(handle_, pBuffer, length);
}


#endif /* HAL_CRC_MODULE_ENABLED */
