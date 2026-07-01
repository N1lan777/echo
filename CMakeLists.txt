cmake_minimum_required(VERSION 3.20)
project(echo C)

find_package(SDL2 CONFIG REQUIRED)

add_executable(echo src/main.c)

target_link_libraries(echo PRIVATE SDL2::SDL2 SDL2::SDL2main)