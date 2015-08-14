#include "duk-user-data.h"
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
            printf("Failed AttachCurrentThread\n");
            abort();
        }
    } else if (getEnvStat == JNI_OK) {
    } else if (getEnvStat == JNI_EVERSION) {
        printf("GetEnv: version not supported\n");
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

jobject duj_value_to_java_object(JNIEnv *env, duk_context *ctx) {
    jobject duktape = getDuktapeUserData(ctx)->duktape;
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
        } else if (duk_is_error(ctx, -1)) {
            retVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukError,
                    methodIdCache.AtReneHollanderDuktapeValuesDukErrorInit,
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

void duj_java_object_to_value(JNIEnv *env, duk_context *ctx, jobject object) {
    if (env->IsInstanceOf(object, classCache.AtReneHollanderDuktapeValuesDukNumber)) {
        duk_push_number(ctx, env->GetDoubleField(object, fieldIdCache.AtReneHollanderDuktapeValuesDukNumberValue));
    } else if (env->IsInstanceOf(object, classCache.AtReneHollanderDuktapeValuesDukBoolean)) {
        duk_push_boolean(ctx, env->GetBooleanField(object, fieldIdCache.AtReneHollanderDuktapeValuesDukBooleanValue));
    } else if (env->IsInstanceOf(object, classCache.AtReneHollanderDuktapeValuesDukString)) {
        jstring jValue = (jstring) env->GetObjectField(object, fieldIdCache.AtReneHollanderDuktapeValuesDukStringValue);
        const char *value = env->GetStringUTFChars(jValue, 0);
        duk_push_string(ctx, value);
        env->ReleaseStringUTFChars(jValue, value);
    } else if (env->IsInstanceOf(object, classCache.AtReneHollanderDuktapeValuesDukUndefined)) {
        duk_push_undefined(ctx);
    } else if (env->IsInstanceOf(object, classCache.AtReneHollanderDuktapeValuesDukNull)) {
        duk_push_null(ctx);
    } else if (env->IsInstanceOf(object, classCache.AtReneHollanderDuktapeValuesDukArray)) {
        int ref = env->GetIntField(object, fieldIdCache.AtReneHollanderDuktapeValuesDukArrayReference);
        duj_push_ref(ctx, ref);
    } else if (env->IsInstanceOf(object, classCache.AtReneHollanderDuktapeValuesDukObject)) {
        int ref = env->GetIntField(object, fieldIdCache.AtReneHollanderDuktapeValuesDukObjectReference);
        duj_push_ref(ctx, ref);
    } else if (env->IsInstanceOf(object, classCache.AtReneHollanderDuktapeValuesDukReferencedValue)) {
        int ref = env->GetIntField(object, fieldIdCache.AtReneHollanderDuktapeValuesAbstractDukReferencedValueReference);
        duj_push_ref(ctx, ref);
    }
}