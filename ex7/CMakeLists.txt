cmake_minimum_required(VERSION 3.3)
project(ex7_project)

enable_testing()

find_package(GTest REQUIRED)
add_subdirectory(test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp fun.cpp)
