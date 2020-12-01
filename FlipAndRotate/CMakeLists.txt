cmake_minimum_required(VERSION 3.17)
project(FlipAndRotate C)

set(CMAKE_C_STANDARD 11)

link_libraries(SDL2)

add_executable(FlipAndRotate main.c)