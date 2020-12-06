cmake_minimum_required(VERSION 3.17)
project(RenderText C)

set(CMAKE_C_STANDARD 11)

link_libraries(SDL2 SDL2_image SDL2_ttf)

add_executable(RenderText main.c DisplayObject.c DisplayObject.h Text.c Text.h)