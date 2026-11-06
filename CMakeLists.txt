cmake_minimum_required(VERSION 4.3)
project(snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(snake
        src/main.cpp
        src/Snake.cpp
        src/Render.cpp
        src/Game.cpp
)

add_compile_definitions(NOCRYPT)