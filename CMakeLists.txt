cmake_minimum_required(VERSION 3.10)
project(measure_overhead)

set(CMAKE_CXX_STANDARD 17)

# Option to enable security flags
option(ENABLE_SECURITY_FLAGS "Enable security flags" OFF)

if(ENABLE_SECURITY_FLAGS)
    message(STATUS "Security flags enabled")

    if (MSVC)
        add_compile_options(/GS)
    else()
        # GCC/Clang
        add_compile_options(-fstack-protector-strong -D_FORTIFY_SOURCE=2)
    endif()
else()
    message(STATUS "Security flags disabled")

    if (MSVC)
        add_compile_options(/GS-)
    endif()
endif()

add_executable(main main.cpp)
