cmake_minimum_required(VERSION 3.10.2)  # CMake version check
project(spellcheck)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.c file of project root directory as source file
set(SOURCE_FILES test_main.c)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(spellcheck ${SOURCE_FILES})

# link project to external libraries (libcheck for testing)
target_link_libraries(spellcheck libcheck)