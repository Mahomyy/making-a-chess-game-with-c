cmake_minimum_required(VERSION 3.26)
project(othello C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED SDL2)
include_directories(othello ${SDL2_INCLUDE_DIRS})

add_executable(othello GUI.c GUI.h main.c
        Game.c)
target_link_libraries(othello ${SDL2_LIBRARIES})

include_directories(opt/homebrew/opt/sdl2/include)
link_directories(/opt/homebrew/lib)
