# Build source list
SET(CPPLIB_FILES src/MyClass.cpp)
SET(CPPLIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/" CACHE INTERNAL "cpplib include directories")
INCLUDE_DIRECTORIES("${CPPLIB_INCLUDE_DIR}")

# Build library
ADD_LIBRARY(cpplib STATIC ${CPPLIB_FILES})
