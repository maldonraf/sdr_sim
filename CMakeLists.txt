cmake_minimum_required(VERSION 3.21)
project(sdr_sim)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(core)
add_subdirectory(tests)