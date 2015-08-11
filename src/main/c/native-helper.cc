#include "native-helper.h"
#include "refs.h"

JNIEXPORT void JNICALL Java_at_renehollander_duktape_NativeHelper_unref(JNIEnv *env, jclass cls, jlong contextPointer, jint ref) {
    duk_context *ctx = (void *) contextPointer;
    duj_unref(ctx, ref);
}