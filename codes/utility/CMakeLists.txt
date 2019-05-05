cmake_minimum_required(VERSION 2.8)

project(utility)

include_directories(./src)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

file(GLOB_RECURSE SRC_FILES "./src/*.cpp" "./src/*.h")

add_executable(utility ${SRC_FILES})
