cmake_minimum_required(VERSION 3.17)
project(CustomCursor C)

set(CMAKE_C_STANDARD 11)

link_libraries(SDL2 SDL2_image)

add_executable(CustomCursor main.c Resource.c Resource.h)