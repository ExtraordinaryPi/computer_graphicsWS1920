
# C++ Practice
# Exercise 1
# 2 Benchmarking and measurement
# 2.2 Microbenchmarking

# `sqrt-pow` application target


cmake_minimum_required(VERSION 3.15)

# dependencies
find_package(CMakeshift 3.6 REQUIRED)
find_package(fmt 6 REQUIRED)

# target
add_executable(sqrt-pow
    "sqrt-pow.cpp")

# properties
target_compile_features(sqrt-pow
    PRIVATE
        cxx_std_20)

# compiler settings
include(CMakeshift/TargetCompileSettings)
cmakeshift_target_compile_settings(sqrt-pow
    PRIVATE
        default)

# library dependencies
target_link_libraries(sqrt-pow
    PRIVATE
        fmt::fmt)

# installation
install(
    TARGETS sqrt-pow)
