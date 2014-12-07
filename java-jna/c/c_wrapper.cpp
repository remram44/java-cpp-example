#include "cpplib/MyClass.h"

#define DLL_EXPORT
/* #define DLL_EXPORT __declspec(dllexport) */

extern "C" DLL_EXPORT MyClass *MyClass_ctor(int nb);
MyClass *MyClass_ctor(int nb)
{
    return new MyClass(nb);
}

extern "C" DLL_EXPORT int MyClass_getValue(const MyClass *self)
{
    return self->getValue();
}

extern "C" DLL_EXPORT void MyClass_increment(MyClass *self)
{
    self->increment();
}
