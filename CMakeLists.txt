project(xdg)

cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS filesystem)

include_directories(
    .

    ${Boost_INCLUDE_DIRS}
)

add_library(xdg xdg.cpp)
set_property(TARGET xdg PROPERTY CXX_STANDARD 11)
target_link_libraries(xdg ${Boost_LIBRARIES})
