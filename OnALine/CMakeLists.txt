cmake_minimum_required(VERSION 3.17)
project(OnALine C)

set(CMAKE_C_STANDARD 11)

link_libraries(SDL2 SDL2_image)

add_executable(OnALine main.c Resource.c Resource.h Cursor.c Cursor.h DisplayObject.c DisplayObject.h Slider.c Slider.h)