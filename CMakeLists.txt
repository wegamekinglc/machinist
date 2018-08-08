cmake_minimum_required(VERSION 3.0)

project(machinist VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()


if(MSVC)
    # Remove warnings
    add_definitions(-D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -stdlib=libc++" )
else()
    set(CMAKE_CXX_STANDARD 14)
endif()

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(source)

