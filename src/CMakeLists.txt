cmake_minimum_required(VERSION 3.8)
project(src)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp loadgraph.cpp loadgraph.h pagerank.cpp pagerank.h)
add_executable(src ${SOURCE_FILES})