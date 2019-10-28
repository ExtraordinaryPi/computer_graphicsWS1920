
# C++ Practice: Exercise 1


## 1. Prologue and public interface
## ================================

cmake_minimum_required(VERSION 3.15)

# Define the project.
project(cpp-practice-ex01
    LANGUAGES CXX)


## 2. Targets
## ==========

add_subdirectory("src/2.1 clock resolution")
add_subdirectory("src/2.2 microbenchmarking")
add_subdirectory("src/2.3 clock latency")
add_subdirectory("src/3.1 fixed-length sequences")
add_subdirectory("src/3.2 flexible-length sequences")
