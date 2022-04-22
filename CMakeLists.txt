cmake_minimum_required(VERSION 3.22)
project(fabrik_demo)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(SDL EXCLUDE_FROM_ALL)

add_executable(fabrik_demo WIN32 main.cpp vector.h renderer.cpp renderer.h bones.cpp bones.h)

target_link_libraries(fabrik_demo SDL2-static SDL2main)
