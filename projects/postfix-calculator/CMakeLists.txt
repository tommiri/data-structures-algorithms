cmake_minimum_required(VERSION 3.25)
project(postfix_calculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(postfix_calculator src/main.cpp src/Stack.cpp)
