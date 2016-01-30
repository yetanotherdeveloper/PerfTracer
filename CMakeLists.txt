cmake_minimum_required(VERSION 2.8)
project(perftracer)

add_definitions(-std=c++11)
set_source_files_properties(main.cpp PROPERTIES COMPILE_FLAGS -finstrument-functions)

add_executable(perftracer_c++_test main.cpp trace.cpp)


