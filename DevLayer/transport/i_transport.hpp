/**
 * @file    i_transport.hpp
 * @brief   通用传输接口。
 * @author  BitWalker
 * @version 1.0.0
 * @date    2026-07-16
 */


#ifndef I_TRANSPORT_HPP
#define I_TRANSPORT_HPP


/* 头文件 ---------------------------------------------------------------- */
#include <cstdint>


/* 类定义 ---------------------------------------------------------------- */
class ITransport {
  public:
    virtual ~ITransport() = default;

    /**
     * @brief  发送数据。
     * @param  data  数据缓冲区指针。
     * @param  len   发送字节数。
     * @return 实际发送字节数，0 表示队列满或其他错误。
     */
    virtual signed short Write(const std::uint8_t *data, std::uint16_t len) = 0;

    /**
     * @brief  接收数据。
     * @param  data  接收缓冲区指针。
     * @param  len   期望读取字节数。
     * @return 实际读取字节数，0 表示无数据。
     */
    virtual signed short Read(std::uint8_t *data, std::uint16_t len) = 0;

    /// @brief 获取当前可用数据字节数。
    [[nodiscard]] virtual std::uint16_t Available() const = 0;
};


#endif /* I_TRANSPORT_HPP */
