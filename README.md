Example of using C++ code from Java
===================================

This repository contains three examples of calling a simple C++ library from Java code.

The library doesn't do anything but contains a class, MyClass, forcing us to support C++ (and not just plain C).

CMake is used to build this, since locating the dependencies got outside the range of my make-fu. The project is supposed to be portable to all major platforms.

Three different wrappers are used, documented below.

SWIG
----

This needs the SWIG tool: http://www.swig.org/

SWIG parses the C++ header file and generated both the C++ JNI code and the Java native and helper classes.

JNA
---

JNA allows Java code to use C dynamic libraries directly. Because our library is in fact C++, a small wrapper is included that wraps it as C code.

You will need the JNA jar to run this: https://github.com/twall/jna

JNI
---

This examples uses JNI directly, without auto-generation. The MyClass class in Java code just declares its methods as being "native", they a reprovided by the dynamic library.
