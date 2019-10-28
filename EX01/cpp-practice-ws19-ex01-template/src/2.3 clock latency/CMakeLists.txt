
# C++ Practice
# Exercise 1
# 2 Benchmarking and measurement
# 2.3 Clock latency

# `clock-latency` application target


cmake_minimum_required(VERSION 3.15)

# dependencies
find_package(CMakeshift 3.6 REQUIRED)
find_package(fmt 6 REQUIRED)

# target
add_executable(clock-latency
    "clock-latency.cpp")

# properties
target_compile_features(clock-latency
    PRIVATE
        cxx_std_20)

# compiler settings
include(CMakeshift/TargetCompileSettings)
cmakeshift_target_compile_settings(clock-latency
    PRIVATE
        default)

# library dependencies
target_link_libraries(clock-latency
    PRIVATE
        fmt::fmt)

# installation
install(
    TARGETS clock-latency)
