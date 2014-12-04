%module mylib
%{
#include "mylib/MyClass.h"
%}

%include "mylib/MyClass.h"

%pragma(java) jniclasscode=%{
    static {
        System.loadLibrary("mylib");
    }
%}
