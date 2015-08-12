#include "native-helper.h"
#include "refs.h"

JNIEXPORT void JNICALL Java_at_renehollander_duktape_NativeHelper__1unref(JNIEnv *env, jclass cls, jlong contextPointer, jint ref) {
    duk_context *ctx = (void *) contextPointer;
    duj_unref(ctx, ref);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_NativeHelper__1mark_1for_1unref(JNIEnv *env, jclass cls, jlong contextPointer, jint ref) {
    duk_context *ctx = (void *) contextPointer;
    duj_mark_for_unref(ctx, ref);
}