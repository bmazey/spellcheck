cmake_minimum_required(VERSION 3.12.1)  # CMake version check
project(spellcheck)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.c file of project root directory as source file
set(SOURCE_FILES main.c)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(spellcheck ${SOURCE_FILES})