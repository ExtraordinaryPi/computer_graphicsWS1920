
# C++ Practice
# Exercise 1
# 2 Benchmarking and measurement
# 2.1 Clock resolution

# `clock-resolution` application target


cmake_minimum_required(VERSION 3.15)

# dependencies
find_package(CMakeshift 3.6 REQUIRED)
find_package(fmt 6 REQUIRED)

set(CMAKE_MAP_IMPORTED_CONFIG_RELWITHDEBINFO "RelWithDebInfo;Release;")

# target
add_executable(clock-resolution
    "clock-resolution.cpp")

# properties
target_compile_features(clock-resolution
    PRIVATE
        cxx_std_20)

# compiler settings
include(CMakeshift/TargetCompileSettings)
cmakeshift_target_compile_settings(clock-resolution
    PRIVATE
        default)

# library dependencies
target_link_libraries(clock-resolution
    PRIVATE
        fmt::fmt)

# installation
install(
    TARGETS clock-resolution)
