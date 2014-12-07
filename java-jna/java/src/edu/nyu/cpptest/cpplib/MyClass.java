package edu.nyu.cpptest.cpplib;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;

public class MyClass {

    public interface CLibrary extends Library {

        CLibrary INSTANCE = (CLibrary)Native.loadLibrary("cpplib_shared",
                CLibrary.class);

        Pointer MyClass_ctor(int nb);

        int MyClass_getValue(Pointer self);

        void MyClass_increment(Pointer self);
    }

    private Pointer self;

    public MyClass(int nb)
    {
        self = CLibrary.INSTANCE.MyClass_ctor(nb);
    }

    public int getValue()
    {
        return CLibrary.INSTANCE.MyClass_getValue(self);
    }

    public void increment()
    {
        CLibrary.INSTANCE.MyClass_increment(self);
    }

}
