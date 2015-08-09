#include <stdlib.h>
#include <duktape_user_data.h>

#include "helper.h"

JavaVM *jvm = NULL;

JNIEnv *getJNIEnv() {
    JNIEnv *env;
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        printf("GetEnv failed.");
        exit(1);
    }
    return env;
}

DuktapeUserData *getDuktapeUserData(duk_context *ctx) {
    duk_memory_functions functions;
    duk_get_memory_functions(ctx, &functions);
    return (DuktapeUserData *) functions.udata;
}