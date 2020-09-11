cmake_minimum_required(VERSION 3.6)
project(xdgcpp VERSION 0.1.0)

include(GNUInstallDirs)

set(XDG_BUILD_TESTS OFF CACHE BOOL "Toggles building of the xdg test suite")

set(XDGCPP_VERSION ${PROJECT_VERSION})

include_directories(.)

add_library(xdgcpp xdg.cpp)
set_property(TARGET xdgcpp PROPERTY CXX_STANDARD 17)
set_target_properties(xdgcpp PROPERTIES PUBLIC_HEADER "xdg.h")

add_executable(xdgcpp-info xdg_info.cpp)
set_property(TARGET xdgcpp-info PROPERTY CXX_STANDARD 17)
target_link_libraries(xdgcpp-info xdgcpp)

if (XDG_BUILD_TESTS)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)

    enable_testing()
    add_definitions(-DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN -DBOOST_TEST_MODULE=xdgcpp)
    add_executable(xdgcpp_test xdg_test.cpp)
    set_property(TARGET xdgcpp_test PROPERTY CXX_STANDARD 17)
    target_link_libraries(xdgcpp_test xdgcpp)
    target_link_libraries(xdgcpp_test ${Boost_LIBRARIES})
    target_include_directories(xdgcpp_test PRIVATE ${Boost_INCLUDE_DIRS})

    add_test(xdgcpp_test xdgcpp_test)
endif()

install(TARGETS xdgcpp xdgcpp-info
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}"
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/pkgconfig/xdgcpp.pc.in"
  "${CMAKE_CURRENT_BINARY_DIR}/pkgconfig/xdgcpp.pc"
  @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pkgconfig/xdgcpp.pc"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")

# EOF #
