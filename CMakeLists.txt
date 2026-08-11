cmake_minimum_required(VERSION 3.20)
project(echo C)

include(FetchContent)
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.x # Скачиваем стабильную ветку 2.x
)
set(FORCE_STATIC_VCRT ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL2)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_executable(echo src/main.c src/sdl_loop.c src/game.c)

target_compile_options(echo PRIVATE
    # GCC, Clang
    $<$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:Clang>>:-Wall;-Wextra;-Wpedantic;-Wshadow>
    # MSVC
    $<$<C_COMPILER_ID:MSVC>:/W4>
)


target_include_directories(echo PRIVATE include)
target_link_libraries(echo PRIVATE SDL2main SDL2-static)
