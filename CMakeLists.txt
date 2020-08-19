cmake_minimum_required(VERSION 2.8.9)
project(gemm_exp)

# Compiler Settings - I used Clang for this, but it will work with GCC too 
SET (CMAKE_CXX_COMPILER "/home/hkhajanchi/10.0.0/src/build/bin/clang++")
SET (CMAKE_CXX_FLAGS "-O3 -g")

# Add src and include directories
include_directories(include)

file(GLOB SOURCES src/*.cpp)
add_executable(gemm_exp ${SOURCES})
