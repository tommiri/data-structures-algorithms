cmake_minimum_required(VERSION 3.25)
project(viikko_8)

set(CMAKE_CXX_STANDARD 20)

add_executable(teht1 teht-1/src/Queue.cpp)
add_executable(teht2 teht-2/src/Queue.cpp teht-2/src/Extended_queue.cpp)
add_executable(teht3 teht-3/src/Queue.cpp teht-3/src/Extended_queue.cpp teht-3/src/main.cpp)
