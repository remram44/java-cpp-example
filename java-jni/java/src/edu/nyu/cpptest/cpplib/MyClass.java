package edu.nyu.cpptest.cpplib;

public class MyClass {

    static {
        System.loadLibrary("cpplib_jni");
    }

    private long self_ptr;

    public MyClass(int nb)
    {
        init(nb);
    }

    private native void init(int nb);

    public native int getValue();

    public native void increment();

    protected native void finalize();

}
