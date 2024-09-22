cmake_minimum_required(VERSION 3.29)

project(lesson_13)

add_subdirectory(lib)


add_executable(lesson_13 src/main.cpp)

target_link_libraries(lesson_13 PRIVATE gate_lib)

set_target_properties(lesson_13 PROPERTIES CXX_STANDARD 20)
