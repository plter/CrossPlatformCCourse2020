cmake_minimum_required(VERSION 3.10)
project(DrawBalls C)

set(CMAKE_C_STANDARD 11)

link_libraries(SDL2 SDL2_image)

add_executable(DrawBalls main.c Ball.c Ball.h Resource.c Resource.h)