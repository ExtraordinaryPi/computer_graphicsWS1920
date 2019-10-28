
# C++ Practice
# Exercise 1
# 3 Iteration and recursion
# 3.2 Flexible-length sequences

# `sequences-benchmark` application target


cmake_minimum_required(VERSION 3.15)

# dependencies
find_package(CMakeshift 3.6 REQUIRED)
find_package(Catch2 2.9 REQUIRED)
find_package(fmt 6 REQUIRED)

# target
add_executable(sequences-benchmark
    "main.cpp"
    "benchmark.cpp"
    "sequences.cpp")

# properties
target_compile_features(sequences-benchmark
    PRIVATE
        cxx_std_20)

# compiler settings
include(CMakeshift/TargetCompileSettings)
cmakeshift_target_compile_settings(sequences-benchmark
    PRIVATE
        default)

# compile-time configuration
target_compile_definitions(sequences-benchmark
    PRIVATE
        CATCH_CONFIG_ENABLE_BENCHMARKING)

# library dependencies
target_link_libraries(sequences-benchmark
    PRIVATE
        fmt::fmt
        Catch2::Catch2)

# installation
install(
    TARGETS sequences-benchmark)
