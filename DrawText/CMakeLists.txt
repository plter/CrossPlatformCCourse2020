cmake_minimum_required(VERSION 3.13)
project(DrawText C)

set(CMAKE_C_STANDARD 11)

link_libraries(SDL2 SDL2_image SDL2_ttf)

add_executable(DrawText main.c)