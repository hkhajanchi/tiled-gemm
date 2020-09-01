cmake_minimum_required(VERSION 2.8.9)
project(gemm_exp)

# Compiler Settings - I used Clang for this, but it will work with GCC too 
SET (CMAKE_CXX_COMPILER "clang++")  
SET (CMAKE_CXX_FLAGS "-O3 -g")
SET (CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Add src and include directories
include_directories(include)
include_directories(src)

# build whatevers in test 
SET (TEST test/basic_gemm.cpp)
add_executable(gemm_exp ${TEST})
