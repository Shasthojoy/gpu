cmake_minimum_required(VERSION 3.5.0)

if (MSVC)
    add_compile_options(/W3 /WX)
else()
    add_compile_options(-W -Wall -Werror -std=c++14)
endif()

add_executable(foo main.cpp gpu/gpu.h gpu/gpu-vk.inl.h)
