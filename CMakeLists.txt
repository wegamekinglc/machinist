cmake_minimum_required(VERSION 3.0)

project(machinist VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

add_subdirectory(source)

