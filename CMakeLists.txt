CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/" ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_FLAGS "-Wall")
PROJECT(java-cpp)

# Testing
OPTION(BUILD_TESTS "Build the test suite (requires CppUnit)" OFF)
IF(BUILD_TESTS)
    ENABLE_TESTING()
ENDIF()

# Recursively build components
ADD_SUBDIRECTORY(cpplib)
ADD_SUBDIRECTORY(java-swig)
ADD_SUBDIRECTORY(java-jna)
ADD_SUBDIRECTORY(java-jni)
