# Require SWIG
FIND_PACKAGE(SWIG REQUIRED)
INCLUDE("${SWIG_USE_FILE}")

# Require JNI
FIND_PACKAGE(JNI REQUIRED)
INCLUDE_DIRECTORIES("${JNI_INCLUDE_DIRS}")

# Build SWIG wrapper
INCLUDE_DIRECTORIES("${CPPLIB_INCLUDE_DIR}")
# TODO: this should really be java/libcpplib.jnilib
SET(CMAKE_SWIG_OUTDIR "${CMAKE_CURRENT_BINARY_DIR}/java/src/edu/nyu/cpptest/cpplib")
SET(CMAKE_SWIG_FLAGS -package edu.nyu.cpptest.cpplib)
SET_SOURCE_FILES_PROPERTIES(swig/cpplib.i PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(cpplib_swig java swig/cpplib.i)
SET_TARGET_PROPERTIES(
    "${SWIG_MODULE_cpplib_swig_REAL_NAME}" PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}")
SWIG_LINK_LIBRARIES(cpplib_swig cpplib)
# Mac OS needs this
FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/swig")

# Require Java
FIND_PACKAGE(Java COMPONENTS Development)
INCLUDE(UseJava)
SET(CMAKE_JAVA_COMPILE_FLAGS "-source" "1.6" "-target" "1.6")

SET(JAVA_SOURCE_FILES
    edu/nyu/cpptest/app/Main.java
    edu/nyu/cpptest/cpplib/MyClass.java
    edu/nyu/cpptest/cpplib/cpplib.java
    edu/nyu/cpptest/cpplib/cpplibJNI.java)

if(WIN32 AND NOT CYGWIN)
    set(_JAVA_SEP ";")
else()
    set(_JAVA_SEP ":")
endif()

# Build Java classes
FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/java/bin")
SET(class_files)
FOREACH(_java_file ${JAVA_SOURCE_FILES})
    # _java_file: relative file name
    # _class_file: relative class name
    # _java_abs_file: absolute file name, in either source or generated dir
    STRING(REGEX MATCH "^edu/nyu/cpptest/cpplib/"
           _is_swig "${_java_file}")
    IF(_is_swig)
        SET(_java_abs_file "${CMAKE_CURRENT_BINARY_DIR}/java/src/${_java_file}")
    ELSE()
        SET(_java_abs_file "${CMAKE_CURRENT_SOURCE_DIR}/java/src/${_java_file}")
    ENDIF()
    STRING(REGEX REPLACE "\\.java$"
           ".class" _class_file
           "${_java_file}")
    ADD_CUSTOM_COMMAND(
        OUTPUT "java/bin/${_class_file}"
        COMMAND
            ${Java_JAVAC_EXECUTABLE}
            ${CMAKE_JAVA_COMPILE_FLAGS}
            -classpath cpplib_swig
            -sourcepath "${CMAKE_CURRENT_SOURCE_DIR}/java/src${_JAVA_SEP}${CMAKE_CURRENT_BINARY_DIR}/java/src"
            -d "${CMAKE_CURRENT_BINARY_DIR}/java/bin"
            "${_java_abs_file}"
        DEPENDS cpplib_swig "${_java_abs_file}")
    LIST(APPEND class_files "java/bin/${_class_file}")
ENDFOREACH()
ADD_CUSTOM_TARGET(JavaSWIGClasses ALL DEPENDS ${class_files})

# TODO: testing
# java -cp java-swig/java/bin -Djava.library.path=java-swig edu.nyu.cpptest.app.Main
