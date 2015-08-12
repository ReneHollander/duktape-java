#include <duktape_user_data.h>
#include <iostream>

#include "helper.h"

JavaVM *jvm = NULL;

JNIEnv *setupJNIEnv() {
    JNIEnv *env;
    // double check it's all ok
    int getEnvStat = jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        std::cout << "GetEnv: not attached" << std::endl;
        if (jvm->AttachCurrentThread((void **) &env, NULL) != 0) {
            std::cout << "Failed to attach" << std::endl;
        }
    } else if (getEnvStat == JNI_OK) {
    } else if (getEnvStat == JNI_EVERSION) {
        std::cout << "GetEnv: version not supported" << std::endl;
    }
    return env;
}

void resetJNIEnv(JNIEnv *env) {
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
    }
    jvm->DetachCurrentThread();
}

DuktapeUserData *getDuktapeUserData(duk_context *ctx) {
    duk_memory_functions functions;
    duk_get_memory_functions(ctx, &functions);
    return (DuktapeUserData *) functions.udata;
}