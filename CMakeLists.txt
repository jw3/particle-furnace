cmake_minimum_required(VERSION 3.12)
project(furnace)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE OFF)

if (NOT EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    message(FATAL_ERROR "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif ()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CONAN_CMAKE_MODULE_PATH} ${CMAKE_MODULE_PATH})

find_package(Particle)
add_particle_remote_app(firmware)
