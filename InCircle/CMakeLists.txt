cmake_minimum_required(VERSION 3.13)
project(InCircle C)

set(CMAKE_C_STANDARD 11)

include_directories("/usr/local/include")

link_libraries(SDL2 SDL2_image)

add_executable(InCircle main.c Resource.c Resource.h Eyeball.c Eyeball.h DisplayObject.c DisplayObject.h)