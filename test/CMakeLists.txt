add_executable(test-tests TestTests.cpp)
target_include_directories(test-tests PRIVATE ${CMAKE_SOURCE_DIR}/firmware ${CONAN_INCLUDE_DIRS_CATCH2})
