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
uint32_t User_CRC::Calculate(uint8_t const pBuffer[],
                             size_t  const byte_length) const noexcept {

    assert_param(pBuffer != nullptr);
    assert_param(byte_length > 0);

    return HAL_CRC_Calculate(handle_,
        reinterpret_cast<uint32_t const *>(pBuffer),
        ToHalBufferLength(byte_length));
}


uint32_t User_CRC::Accumulate(uint8_t const pBuffer[],
                              size_t  const byte_length) const noexcept {

    assert_param(pBuffer != nullptr);
    assert_param(byte_length > 0);

    return HAL_CRC_Accumulate(handle_,
        reinterpret_cast<uint32_t const *>(pBuffer),
        ToHalBufferLength(byte_length));
}


uint32_t User_CRC::ToHalBufferLength(size_t const byte_length) const noexcept {

    switch (handle_->InputDataFormat) {
        case CRC_INPUTDATA_FORMAT_BYTES:
            return byte_length;

        case CRC_INPUTDATA_FORMAT_HALFWORDS:
            assert_param((byte_length % sizeof(uint16_t)) == 0);
            return byte_length / sizeof(uint16_t);

        case CRC_INPUTDATA_FORMAT_WORDS:
            assert_param((byte_length % sizeof(uint32_t)) == 0);
            return byte_length / sizeof(uint32_t);

        default:
            assert_param(false);
            return byte_length;
    }
}


#endif /* HAL_CRC_MODULE_ENABLED */