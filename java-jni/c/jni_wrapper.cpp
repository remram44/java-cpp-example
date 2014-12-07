#include "cpplib/MyClass.h"
#include "MyClass_jni.h"

static jfieldID _get_self_id(JNIEnv *env, jobject thisObj)
{
    static int init = 0;
    static jfieldID fidSelfPtr;
    if(!init)
    {
        jclass thisClass = env->GetObjectClass(thisObj);
        fidSelfPtr = env->GetFieldID(thisClass, "self_ptr", "J");
    }
    return fidSelfPtr;
}

static MyClass *_get_self(JNIEnv *env, jobject thisObj)
{
    jlong selfPtr = env->GetLongField(thisObj, _get_self_id(env, thisObj));
    return *(MyClass**)&selfPtr;
}

static void _set_self(JNIEnv *env, jobject thisObj, MyClass *self)
{
    jlong selfPtr = *(jlong*)&self;
    env->SetLongField(thisObj, _get_self_id(env, thisObj), selfPtr);
}


JNIEXPORT void JNICALL Java_edu_nyu_cpptest_cpplib_MyClass_init(JNIEnv *env, jobject thisObj, jint nb)
{
    MyClass *self = new MyClass(nb);
    _set_self(env, thisObj, self);
}

JNIEXPORT jint JNICALL Java_edu_nyu_cpptest_cpplib_MyClass_getValue(JNIEnv *env, jobject thisObj)
{
    MyClass *self = _get_self(env, thisObj);
    return self->getValue();
}

JNIEXPORT void JNICALL Java_edu_nyu_cpptest_cpplib_MyClass_increment(JNIEnv *env, jobject thisObj)
{
    MyClass *self = _get_self(env, thisObj);
    self->increment();
}

JNIEXPORT void JNICALL Java_edu_nyu_cpptest_cpplib_MyClass_finalize(JNIEnv *env, jobject thisObj)
{
    MyClass *self = _get_self(env, thisObj);
    if(self != NULL)
    {
        delete self;
        _set_self(env, thisObj, NULL);
    }
}
