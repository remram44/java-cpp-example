# Require Java
FIND_PACKAGE(Java COMPONENTS Development)
INCLUDE(UseJava)
SET(CMAKE_JAVA_COMPILE_FLAGS "-source" "1.6" "-target" "1.6")

SET(JAVA_SOURCE_FILES
    edu/nyu/cpptest/app/Main.java
    edu/nyu/cpptest/cpplib/MyClass.java)

# Build Java classes
FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/java/bin")
SET(class_files)
FOREACH(_java_file ${JAVA_SOURCE_FILES})
    # _java_file: relative file name
    # _class_file: relative class name
    STRING(REGEX REPLACE "\\.java$"
           ".class" _class_file
           "${_java_file}")
    ADD_CUSTOM_COMMAND(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/java/bin/${_class_file}"
        COMMAND
            ${Java_JAVAC_EXECUTABLE}
            ${CMAKE_JAVA_COMPILE_FLAGS}
            -sourcepath "${CMAKE_CURRENT_SOURCE_DIR}/java/src"
            -d "${CMAKE_CURRENT_BINARY_DIR}/java/bin"
            "${CMAKE_CURRENT_SOURCE_DIR}/java/src/${_java_file}"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/java/src/${_java_file}")
    LIST(APPEND class_files "java/bin/${_class_file}")
ENDFOREACH()
ADD_CUSTOM_TARGET(JavaJNIClasses ALL DEPENDS ${class_files})

# Make the JNI header file
ADD_CUSTOM_COMMAND(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/include/MyClass_jni.h"
    COMMAND
        ${Java_JAVAH_EXECUTABLE}
        -o "${CMAKE_CURRENT_BINARY_DIR}/include/MyClass_jni.h"
        -classpath "${CMAKE_CURRENT_BINARY_DIR}/java/bin"
        edu.nyu.cpptest.cpplib.MyClass
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/java/bin/edu/nyu/cpptest/cpplib/MyClass.class")
ADD_CUSTOM_TARGET(JavaJNIHeaders ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/include/MyClass_jni.h")

# Require JNI
FIND_PACKAGE(JNI REQUIRED)

# Builds the JNI wrapper
INCLUDE_DIRECTORIES("${CPPLIB_INCLUDE_DIR}"
                    "${CMAKE_CURRENT_BINARY_DIR}/include"
                    ${JNI_INCLUDE_DIRS})
ADD_LIBRARY(cpplib_jni SHARED c/jni_wrapper.cpp)
SET_TARGET_PROPERTIES(
    cpplib_jni PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}")
TARGET_LINK_LIBRARIES(cpplib_jni cpplib)
ADD_DEPENDENCIES(cpplib_jni JavaJNIHeaders)

# TODO: testing
# java -cp java-jni/java/bin -Djava.library.path=java-jni edu.nyu.cpptest.app.Main
