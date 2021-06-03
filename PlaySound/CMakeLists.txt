cmake_minimum_required(VERSION 3.13)
project(PlaySound C)

set(CMAKE_C_STANDARD 11)

link_libraries(SDL2)

add_executable(PlaySound main.c)