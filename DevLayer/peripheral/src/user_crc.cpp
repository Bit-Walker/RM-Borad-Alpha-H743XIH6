/* 头文件 ---------------------------------------------------------------- */
#include "peripheral/user_crc.hpp"

/* 条件编译 --------------------------------------------------------------- */
#ifdef HAL_CRC_MODULE_ENABLED


/* 构造函数 --------------------------------------------------------------- */
User_crc::User_crc(const CRC_HandleTypeDef *const handle) noexcept
    : handle_(*handle) {

    assert_param(handle != nullptr);
}


/* 成员方法 --------------------------------------------------------------- */
std::uint32_t User_crc::Calculate(std::uint32_t pBuffer[],
                                  std::uint32_t const length) noexcept {
    assert_param(pBuffer != nullptr);
    assert_param(length > 0);

    return HAL_CRC_Calculate(&handle_, pBuffer, length);
}


std::uint32_t User_crc::Accumulate(std::uint32_t pBuffer[],
                                   std::uint32_t const length) noexcept {
    assert_param(pBuffer != nullptr);
    assert_param(length > 0);

    return HAL_CRC_Accumulate(&handle_, pBuffer, length);
}


void User_crc::Reset() const noexcept {
    __HAL_CRC_DR_RESET(&handle_);
}


void User_crc::SetInitValue(std::uint32_t const value) const noexcept {
    __HAL_CRC_INITIALCRCVALUE_CONFIG(&handle_, value);
}


std::uint32_t User_crc::GetPolynomial() const noexcept {
    return handle_.Init.GeneratingPolynomial;
}


std::uint32_t User_crc::GetCRCLength() const noexcept {
    return handle_.Init.CRCLength;
}


std::uint32_t User_crc::GetInitValue() const noexcept {
    return handle_.Init.InitValue;
}


#endif /* HAL_CRC_MODULE_ENABLED */
