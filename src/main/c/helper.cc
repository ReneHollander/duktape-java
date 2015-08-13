#include "duk-user-data.h"
#include <iostream>
#include "helper.h"
#include "cache.h"
#include "refs.h"

JavaVM *jvm = NULL;

JNIEnv *setupJNIEnv() {
    JNIEnv *env;
    // double check it's all ok
    int getEnvStat = jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        if (jvm->AttachCurrentThread((void **) &env, NULL) != 0) {
            std::cout << "Failed to attach" << std::endl;
            abort();
        }
    } else if (getEnvStat == JNI_OK) {
    } else if (getEnvStat == JNI_EVERSION) {
        std::cout << "GetEnv: version not supported" << std::endl;
        abort();
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

jobject duj_value_to_java_object(JNIEnv *env, duk_context *ctx, jobject duktape) {
    int type = duk_get_type(ctx, -1);
    jobject retVal = NULL;
    if (type == DUK_TYPE_NUMBER) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukNumber,
                methodIdCache.AtReneHollanderDuktapeValuesDukNumberInit,
                duktape,
                duk_get_number(ctx, -1)
        );
    } else if (type == DUK_TYPE_BOOLEAN) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukBoolean,
                methodIdCache.AtReneHollanderDuktapeValuesDukBooleanInit,
                duktape,
                duk_get_boolean(ctx, -1)
        );
    } else if (type == DUK_TYPE_STRING) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukString,
                methodIdCache.AtReneHollanderDuktapeValuesDukStringInit,
                duktape,
                env->NewStringUTF(duk_get_string(ctx, -1))
        );
    } else if (type == DUK_TYPE_NULL) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukNull,
                methodIdCache.AtReneHollanderDuktapeValuesDukNullInit,
                duktape
        );
    } else if (type == DUK_TYPE_OBJECT) {
        duk_dup(ctx, -1);
        int objectRef = duj_ref(ctx);

        if (duk_is_array(ctx, -1)) {
            retVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukArray,
                    methodIdCache.AtReneHollanderDuktapeValuesDukArrayInit,
                    duktape,
                    objectRef
            );
        } else if (duk_is_function(ctx, -1)) {
            retVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukFunction,
                    methodIdCache.AtReneHollanderDuktapeValuesDukFunctionInit,
                    duktape,
                    objectRef
            );
        } else {
            retVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukObject,
                    methodIdCache.AtReneHollanderDuktapeValuesDukObjectInit,
                    duktape,
                    objectRef
            );
        }
    } else {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukUndefined,
                methodIdCache.AtReneHollanderDuktapeValuesDukUndefinedInit,
                duktape
        );
    }
    duk_pop(ctx);
    return retVal;
}