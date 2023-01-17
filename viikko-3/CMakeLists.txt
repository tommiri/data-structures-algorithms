cmake_minimum_required(VERSION 3.24)
project(viikko_3)

set(CMAKE_CXX_STANDARD 20)

add_executable(teht1 teht-1/src/main.cpp teht-1/src/Life.cpp teht-1/include/Life.h teht-1/src/Utility.cpp
        teht-1/include/Utility.h)
add_executable(teht2 teht-2/src/main.cpp teht-2/src/Life.cpp teht-2/include/Life.h teht-2/src/Utility.cpp
        teht-2/include/Utility.h)
add_executable(teht3 teht-3/src/main.cpp teht-3/src/Life.cpp teht-3/include/Life.h teht-3/src/Utility.cpp
        teht-3/include/Utility.h)
