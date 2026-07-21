
include_directories(Library/SEGGER_RTT)
file(GLOB_RECURSE RTT_C_SRC "Library/SEGGER_RTT/src/*.c")
file(GLOB_RECURSE RTT_S_SRC "Library/SEGGER_RTT/src/*.S")
list(APPEND SOURCES ${RTT_C_SRC} ${RTT_S_SRC})
