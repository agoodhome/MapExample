cmake_minimum_required(VERSION 3.17)
project(CS301_Examples)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(Hash_Example Map_usage_example.cpp MapT.h)