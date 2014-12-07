%module cpplib
%{
#include "cpplib/MyClass.h"
%}

%include "cpplib/MyClass.h"

%pragma(java) jniclasscode=%{
    static {
        System.loadLibrary("cpplib_swig");
    }
%}
