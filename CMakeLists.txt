cmake_minimum_required(VERSION 3.6)
project(xdgcpp VERSION 0.1.0)

cmake_minimum_required(VERSION 2.8)

# We have to manually alter the cxx flags to have a working
# travis-ci build. Its container-based infrastructure only features
# a very old cmake that does not support the more current:
#   set_property(TARGET xdg_test PROPERTY CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include(GNUInstallDirs)

set(XDG_BUILD_TESTS ON CACHE BOOL "Toggles building of the xdg test suite")

set(XDGCPP_VERSION ${PROJECT_VERSION})

find_package(Boost COMPONENTS filesystem system unit_test_framework REQUIRED)

include_directories(
    .
    ${Boost_INCLUDE_DIRS}
)

add_library(xdgcpp xdg.cpp)
set_property(TARGET xdgcpp PROPERTY CXX_STANDARD 11)
set_target_properties(xdgcpp PROPERTIES PUBLIC_HEADER "xdg.h")
target_link_libraries(xdgcpp ${Boost_LIBRARIES})

add_executable(xdg-info xdg_info.cpp)
target_link_libraries(xdg-info xdgcpp)

if (XDG_BUILD_TESTS)
    enable_testing()
    add_definitions(-DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN -DBOOST_TEST_MODULE=xdg)
    add_executable(xdg_test xdg_test.cpp)
    set_property(TARGET xdg_test PROPERTY CXX_STANDARD 11)
    target_link_libraries(xdg_test xdgcpp)

    add_test(xdg_test xdg_test)
endif()

install(TARGETS xdgcpp xdg-info
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}"
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/pkgconfig/xdgcpp.pc.in"
  "${CMAKE_CURRENT_BINARY_DIR}/pkgconfig/xdgcpp.pc"
  @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pkgconfig/xdgcpp.pc"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")

# EOF #
