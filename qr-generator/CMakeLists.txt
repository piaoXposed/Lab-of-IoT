cmake_minimum_required(VERSION 3.16)
project(qr_generator)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs)
include_directories(src)
add_subdirectory(src)