add_library(states STATIC states.hpp states.cpp)

####################################
# todo;; need to provide better way for custom libs to obtain platform settings
#
include(${PLATFORM})
target_compile_options(states PRIVATE "$<$<CONFIG:ALL>:${PLATFORM_CXX_FLAGS}>")
target_include_directories(states PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PLATFORM_CXX_INCLUDES})
target_compile_definitions(states PRIVATE ${PLATFORM_CXX_DEFS})
set_target_properties(states PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
#
####################################
