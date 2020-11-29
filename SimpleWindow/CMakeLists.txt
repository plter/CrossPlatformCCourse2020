cmake_minimum_required(VERSION 3.17)
project(SimpleWindow C)

set(CMAKE_C_STANDARD 11)

link_libraries(SDL2)

add_executable(SimpleWindow main.c)