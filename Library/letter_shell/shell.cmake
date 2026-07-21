
include_directories(Library/letter_shell)
file(GLOB_RECURSE SHELL_SRC "Library/letter_shell/src/*.c")
list(APPEND SOURCES ${SHELL_SRC})
