cmake_minimum_required(VERSION 2.8)
project(perftracer)

add_definitions(-std=c++11)
set_source_files_properties(main.cpp PROPERTIES COMPILE_FLAGS -finstrument-functions)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(perftracer_c++_test main.cpp trace.cpp)
target_link_libraries(perftracer_c++_test dl)


