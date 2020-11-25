set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
cmake_minimum_required(VERSION 3.17)
project(furnace)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE OFF)

if (NOT EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    message(FATAL_ERROR "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif ()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS TARGETS)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(PLATFORM xenon)

find_package(Particle)
particle_app(firmware)
