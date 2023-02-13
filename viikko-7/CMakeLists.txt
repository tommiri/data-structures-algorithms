cmake_minimum_required(VERSION 3.25)
project(viikko_7)

set(CMAKE_CXX_STANDARD 20)

add_executable(teht-1 teht1/src/main.cpp teht1/src/Extended_queue.cpp teht1/src/Queue.cpp)
add_executable(teht-3 teht3/src/main.cpp teht3/src/Extended_stack.cpp teht3/src/Extended_queue.cpp teht3/src/Queue.cpp)
add_executable(teht-4 teht4/src/main.cpp teht4/src/Extended_stack.cpp teht4/src/Extended_queue.cpp teht4/src/Queue.cpp)
