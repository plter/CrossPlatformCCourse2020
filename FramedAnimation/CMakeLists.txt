cmake_minimum_required(VERSION 3.10)
project(FramedAnimation C)

set(CMAKE_C_STANDARD 11)

link_libraries(SDL2 SDL2_image)

add_executable(FramedAnimation main.c Resource.c Resource.h DisplayObject.c DisplayObject.h WalkAnimation.c WalkAnimation.h)