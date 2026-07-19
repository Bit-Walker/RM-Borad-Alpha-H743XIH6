/**
 * @file    cmd_typeof.cpp
 * @brief   打印 C++ 各种数据类型的内存占用
 * @author  BitWalker
 * @version 1.0.0
 * @date    2026-07-19
 *
 */

#include "../shell_port.h"

#include <cstdint>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <deque>


#ifdef __cplusplus
extern "C" {
#endif


/* 函数 --------------------------------------------------------------- */

int shellTypeof(int argc, char *argv[])
{
    Shell *s = shellGetCurrent();
    if (!s) return -1;

    shellWriteString(s, "\r\n");
    shellPrint(s, "==================================== \r\n");
    shellPrint(s, "   C++ Data Type Sizes               \r\n");
    shellPrint(s, "   Platform: ARM Cortex-M7 32-bit    \r\n");
    shellPrint(s, "==================================== \r\n\r\n");

    /* ---- 基础类型 ---- */
    shellWriteString(s, "基础类型\r\n");
    shellPrint(s, "  bool                 : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(bool)));
    shellPrint(s, "  char                 : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(char)));
    shellPrint(s, "  wchar_t              : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(wchar_t)));
    shellPrint(s, "  short                : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(short)));
    shellPrint(s, "  int                  : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(int)));
    shellPrint(s, "  long                 : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(long)));
    shellPrint(s, "  long long            : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(long long)));
    shellPrint(s, "  float                : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(float)));
    shellPrint(s, "  double               : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(double)));
    shellPrint(s, "  long double          : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(long double)));
    shellPrint(s, "  void*                : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(void *)));
    shellPrint(s, "  nullptr_t            : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(std::nullptr_t)));
    shellWriteString(s, "\r\n");

    shellWriteString(s, "定宽整型\r\n");
    shellPrint(s, "  int8_t               : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(int8_t)));
    shellPrint(s, "  uint8_t              : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(uint8_t)));
    shellPrint(s, "  int16_t              : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(int16_t)));
    shellPrint(s, "  uint16_t             : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(uint16_t)));
    shellPrint(s, "  int32_t              : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(int32_t)));
    shellPrint(s, "  uint32_t             : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(uint32_t)));
    shellPrint(s, "  int64_t              : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(int64_t)));
    shellPrint(s, "  uint64_t             : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(uint64_t)));
    shellPrint(s, "  intptr_t             : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(intptr_t)));
    shellPrint(s, "  size_t               : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(size_t)));
    shellPrint(s, "  ptrdiff_t            : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(ptrdiff_t)));
    shellWriteString(s, "\r\n");

    shellWriteString(s, "标准模板库容器\r\n");
    shellPrint(s, "  std::string          : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(std::string)));
    shellPrint(s, "  std::vector<int>     : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(std::vector<int>)));
    shellPrint(s, "  std::list<int>       : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(std::list<int>)));
    shellPrint(s, "  std::deque<int>      : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(std::deque<int>)));
    shellPrint(s, "  std::set<int>        : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(std::set<int>)));
    shellPrint(s, "  std::map<int,int>    : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(std::map<int, int>)));
    shellPrint(s, "  std::unordered_map   : %2u byte(s)\r\n", static_cast<unsigned>(sizeof(std::unordered_map<int, int>)));
    shellWriteString(s, "\r\n");

    return 0;
}

#ifdef __cplusplus
}
#endif
