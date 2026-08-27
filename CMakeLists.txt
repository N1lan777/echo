cmake_minimum_required(VERSION 3.20)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "" FORCE)

project(echo C)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

include(FetchContent)
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.x # Скачиваем стабильную ветку 2.x
)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL2TTF_VENDORED ON CACHE BOOL "" FORCE)
set(FORCE_STATIC_VCRT ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG        release-2.22.0
)
FetchContent_MakeAvailable(SDL2_ttf)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(echo src/main.c src/sdl_loop.c src/game.c src/trifles.c)

target_compile_options(echo PRIVATE
    # GCC, Clang
    $<$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:Clang>>:-Wall;-Wextra;-Wpedantic;-Wshadow>
    # MSVC
    $<$<C_COMPILER_ID:MSVC>:/W4>
)


target_include_directories(echo PRIVATE include)
target_link_libraries(echo PRIVATE SDL2main SDL2-static SDL2_ttf)
