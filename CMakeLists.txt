cmake_minimum_required(VERSION 3.0)

project(machinist VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

option(BUILD_SHARED_LIBS "Build shared libraries" False)
option(USE_BOOST_DYNAMIC_LIBRARIES "Use the shared version of Boost libraries" ${UNIX})
if (USE_BOOST_DYNAMIC_LIBRARIES)
    add_definitions(-DBOOST_ALL_DYN_LINK)
else()
    set(Boost_USE_STATIC_LIBS ON)
endif()


if(MSVC)
    # Remove warnings
    INCLUDE_DIRECTORIES($ENV{GTEST_ROOT}/include)
    link_directories($ENV{GTEST_ROOT}/lib/${CMAKE_BUILD_TYPE}/MD)
    link_directories($ENV{BOOST_ROOT}/stage/lib)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -stdlib=libc++" )
else()
    set(CMAKE_CXX_STANDARD 14)
endif()
add_definitions(-DPROJECT_SOURCE="${CMAKE_SOURCE_DIR}")

find_package(Boost)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif (Boost_FOUND)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(source)
add_subdirectory(machinist)
add_subdirectory(tests)

