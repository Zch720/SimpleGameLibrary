cmake_minimum_required(VERSION 3.14)
project(simple_game_library_ext)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(glad OBJECT glad/src/gl.c)
target_include_directories(glad PUBLIC glad/include)

add_subdirectory(glfw)