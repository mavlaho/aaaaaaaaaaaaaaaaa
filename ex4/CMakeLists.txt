cmake_minimum_required(VERSION 3.2)

project(ex4_project)

find_package(Boost 1.54 REQUIRED COMPONENTS filesystem)

add_executable(ex4prog main.cpp)
target_link_libraries(ex4prog  Boost::filesystem)


set_target_properties(ex4prog
  PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
  )
