#include "duk-buffer.h"
#include "duktape.h"
#include "refs.h"

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_value_object_DukBuffer__1createDukBuffer(JNIEnv *env, jclass cls, jlong contextPointer, jint size) {
    duk_context *ctx = (void *) contextPointer;
    duk_push_fixed_buffer(ctx, (duk_size_t) size);
    int ref = duj_ref(ctx);
    return ref;
}

JNIEXPORT jobject JNICALL Java_at_renehollander_duktape_value_object_DukBuffer__1getByteBuffer(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_size_t sz;
    void *ptr = duk_get_buffer(ctx, -1, &sz);
    jobject buffer = env->NewDirectByteBuffer(ptr, (jlong) sz);
    duk_pop(ctx);
    return buffer;
}