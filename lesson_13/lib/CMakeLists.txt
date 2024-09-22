cmake_minimum_required(VERSION 3.29)

project(GateLib)

add_library(gate_lib STATIC gate.cpp)

target_include_directories(gate_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(gate_lib PROPERTIES CXX_STANDARD 17)