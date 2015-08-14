#include <string>
#include "refs.h"
#include "duk-error.h"

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_values_DukError__1createDukError(JNIEnv *env, jclass cls, jlong contextPointer, jint errorCode, jstring jMessage) {
    duk_context *ctx = (void *) contextPointer;
    const char *message = env->GetStringUTFChars(jMessage, 0);
    duk_push_error_object(ctx, errorCode, message);
    int ref = duj_ref(ctx);
    env->ReleaseStringUTFChars(jMessage, message);
    return ref;
}

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_values_DukError__1getErrorCode(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    int code = duk_get_error_code(ctx, -1);
    duk_pop(ctx);
    return code;
}

JNIEXPORT jstring JNICALL Java_at_renehollander_duktape_values_DukError__1getErrorMessage(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_get_prop_string(ctx, -1, "stack");
    std::string errorMsg(duk_safe_to_string(ctx, -1));
    jstring message = env->NewStringUTF(errorMsg.c_str());
    duk_pop_2(ctx);
    return message;
}
