add_library(fsm STATIC fsm.hpp fsm.cpp)

####################################
# todo;; need to provide better way for custom libs to obtain platform settings
#
include(${PLATFORM})
target_compile_options(fsm PRIVATE "$<$<CONFIG:ALL>:${PLATFORM_CXX_FLAGS}>")
target_include_directories(fsm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PLATFORM_CXX_INCLUDES})
target_compile_definitions(fsm PRIVATE ${PLATFORM_CXX_DEFS})
set_target_properties(fsm PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
#
####################################
