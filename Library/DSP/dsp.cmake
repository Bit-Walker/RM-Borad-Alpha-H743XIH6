
set(ROOT ${CMAKE_SOURCE_DIR})
add_subdirectory(Library/DSP/Source)
cmake_language(DEFER CALL target_link_libraries ${PROJECT_NAME}.elf CMSISDSP)
