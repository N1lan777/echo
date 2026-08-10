cmake_minimum_required(VERSION 3.20)
project(echo C)

find_package(SDL2 CONFIG REQUIRED)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(echo src/main.c src/sdl_loop.c src/game.c)

target_compile_options(echo PRIVATE
    # GCC, Clang
    $<$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:Clang>>:-Wall;-Wextra;-Wpedantic;-Wshadow>
    # MSVC
    $<$<C_COMPILER_ID:MSVC>:/W4>
)


target_include_directories(echo PRIVATE include)
target_link_libraries(echo PRIVATE SDL2::SDL2 SDL2::SDL2main)
