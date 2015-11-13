project(xdg)

cmake_minimum_required(VERSION 2.8)

include_directories(.)
add_library(xdg xdg.cpp)

set_property(TARGET xdg PROPERTY CXX_STANDARD 11)
