cmake_minimum_required(VERSION 3.25)
project(viikko_11)

set(CMAKE_CXX_STANDARD 20)

add_executable(teht-1 teht-1/src/main.cpp teht-1/src/Queue.cpp teht-1/src/Node.cpp)
add_executable(teht-2 teht-2/src/main.cpp teht-2/src/Queue.cpp teht-2/src/Node.cpp teht-2/src/Extended_queue.cpp)
add_executable(teht-3 teht-3/src/main.cpp teht-3/src/Queue.cpp teht-3/src/Node.cpp teht-3/src/Extended_queue.cpp)
