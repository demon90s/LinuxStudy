cmake_minimum_required(VERSION 2.8)

project(utility)

include_directories(./src)

file(GLOB_RECURSE SRC_FILES "./src/*.cpp" "./src/*.h")

add_executable(utility ${SRC_FILES})
