cmake_minimum_required(VERSION 3.10)

project(F100Lib VERSION 0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")

add_library(F100Lib STATIC ${SOURCES})

target_include_directories(F100Lib PUBLIC include)
