#include "duk-function.h"
#include "duktape.h"
#include "refs.h"
#include "helper.h"

JNIEXPORT jobject JNICALL Java_at_renehollander_duktape_value_object_DukFunction__1invoke(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jobjectArray arguments) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    jsize argc = env->GetArrayLength(arguments);
    for (int i = 0; i < argc; i++) {
        jobject argument = env->GetObjectArrayElement(arguments, i);
        duj_java_object_to_value(env, ctx, argument);
    }
    duk_pcall(ctx, argc);
    return duj_value_to_java_object(env, ctx);
}