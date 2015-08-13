#include <cache.h>
#include "duk-function.h"
#include "duktape.h"
#include "refs.h"
#include "helper.h"

JNIEXPORT jobject JNICALL Java_at_renehollander_duktape_values_DukFunction__1invoke(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jobjectArray arguments) {
    duk_context *ctx = (void *) contextPointer;
    DuktapeUserData *userData = getDuktapeUserData(ctx);
    duj_push_ref(ctx, objectRef);

    jsize argc = env->GetArrayLength(arguments);

    for (int i = 0; i < argc; i++) {
        jobject argument = env->GetObjectArrayElement(arguments, i);
        duj_java_object_to_value(env, ctx, argument);
    }

    jobject retVal = NULL;
    int rc = duk_pcall(ctx, argc);
    if (rc == DUK_EXEC_SUCCESS) {
        retVal = duj_value_to_java_object(env, ctx, userData->duktape);
    } else {
        printf("error: %s\n", duk_to_string(ctx, -1));
        duk_pop(ctx);
    }

    return retVal;
}