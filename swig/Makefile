LIBRARY=java/bin/libmylib.jnilib

.PHONY: all run

all: ${LIBRARY}

${LIBRARY}: swig/mylib_wrap.cxx
	g++ -shared -Icpp -o $@ swig/mylib_wrap.cxx cpp/mylib/MyClass.cpp

swig/mylib_wrap.cxx: swig/mylib.i cpp/mylib/MyClass.h cpp/mylib/MyClass.cpp
	mkdir -p java/src/edu/nyu/cpptest/mylib
	swig -java -c++ -package edu.nyu.cpptest.mylib -outdir java/src/edu/nyu/cpptest/mylib -Icpp swig/mylib.i

run: all
	java -cp java/bin -Djava.library.path=java/bin edu.nyu.cpptest.app.Main
