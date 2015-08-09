#include "objectwrapper.h"

jobject wrapInteger(JNIEnv *env, jint i) {
    return env->NewObject(classCache.JavaLangInteger, methodIdCache.JavaLangIntegerInit, i);
}

jobject wrapLong(JNIEnv *env, jlong l) {
    return env->NewObject(classCache.JavaLangLong, methodIdCache.JavaLangLongInit, l);
}