LIBRARY=java/bin/libmylib.jnilib

SWIG_JAVA=java/src/edu/nyu/cpptest/mylib/MyClass.java \
	java/src/edu/nyu/cpptest/mylib/mylib.java \
	java/src/edu/nyu/cpptest/mylib/mylibJNI.java

.PHONY: all java run clean

all: ${LIBRARY} java

java/bin:
	mkdir -p java/bin

${LIBRARY}: swig/mylib_wrap.cxx java/bin
	g++ -shared -Icpp -o $@ swig/mylib_wrap.cxx cpp/mylib/MyClass.cpp

swig/mylib_wrap.cxx ${SWIG_JAVA}: swig/mylib.i cpp/mylib/MyClass.h cpp/mylib/MyClass.cpp
	mkdir -p java/src/edu/nyu/cpptest/mylib
	swig -java -c++ -package edu.nyu.cpptest.mylib -outdir java/src/edu/nyu/cpptest/mylib -Icpp swig/mylib.i

run: all
	java -cp java/bin -Djava.library.path=java/bin edu.nyu.cpptest.app.Main

java: java/bin/edu/nyu/cpptest/app/Main.class \
	java/bin/edu/nyu/cpptest/mylib/MyClass.class \
	java/bin/edu/nyu/cpptest/mylib/mylib.class \
	java/bin/edu/nyu/cpptest/mylib/mylibJNI.class

java/bin/%.class: java/src/%.java java/bin
	javac -sourcepath java/src -d java/bin $<

clean:
	rm -Rf java/bin
	rm -Rf java/src/edu/nyu/cpptest/mylib
	rm -f swig/mylib_wrap.cxx
