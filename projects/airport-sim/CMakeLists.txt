cmake_minimum_required(VERSION 3.26)
project(airport_sim)

set(CMAKE_CXX_STANDARD 20)

add_executable(airport_sim src/main.cpp src/Runway.cpp include/Runway.h src/Plane.cpp include/Plane.h src/Random.cpp include/Random.h src/Queue.cpp include/Queue.h include/helper_functions.h)