cmake_minimum_required(VERSION 3.26)
project(cpplatformer)

set(CMAKE_CXX_STANDARD 17)
find_package(raylib CONFIG REQUIRED)
add_executable(cpplatformer main.cpp)
target_link_libraries(cpplatformer PRIVATE raylib)
