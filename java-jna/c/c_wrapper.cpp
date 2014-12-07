#include "cpplib/MyClass.h"

#ifdef _WIN32
#   define DLL_EXPORT __declspec(dllexport)
#else
#   define DLL_EXPORT
#endif

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
