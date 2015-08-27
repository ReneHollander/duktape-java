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
                classCache.at.renehollander.duktape.value.primitive.DukNumber,
                methodIdCache.at.renehollander.duktape.value.primitive.DukNumber.init,
                duktape,
                duk_get_number(ctx, -1)
        );
    } else if (type == DUK_TYPE_BOOLEAN) {
        retVal = env->NewObject(
                classCache.at.renehollander.duktape.value.primitive.DukBoolean,
                methodIdCache.at.renehollander.duktape.value.primitive.DukBoolean.init,
                duktape,
                duk_get_boolean(ctx, -1)
        );
    } else if (type == DUK_TYPE_STRING) {
        retVal = env->NewObject(
                classCache.at.renehollander.duktape.value.primitive.DukString,
                methodIdCache.at.renehollander.duktape.value.primitive.DukString.init,
                duktape,
                env->NewStringUTF(duk_get_string(ctx, -1))
        );
    } else if (type == DUK_TYPE_NULL) {
        retVal = env->NewObject(
                classCache.at.renehollander.duktape.value.primitive.DukNull,
                methodIdCache.at.renehollander.duktape.value.primitive.DukNull.init,
                duktape
        );
    } else if (type == DUK_TYPE_BUFFER) {
        duk_dup(ctx, -1);
        int objectRef = duj_ref(ctx);
        retVal = env->NewObject(
                classCache.at.renehollander.duktape.value.object.DukBuffer,
                methodIdCache.at.renehollander.duktape.value.object.DukBuffer.init,
                duktape,
                objectRef
        );
    } else if (type == DUK_TYPE_OBJECT) {
        duk_dup(ctx, -1);
        int objectRef = duj_ref(ctx);

        if (duk_is_array(ctx, -1)) {
            retVal = env->NewObject(
                    classCache.at.renehollander.duktape.value.object.DukArray,
                    methodIdCache.at.renehollander.duktape.value.object.DukArray.init,
                    duktape,
                    objectRef
            );
        } else if (duk_is_function(ctx, -1)) {
            retVal = env->NewObject(
                    classCache.at.renehollander.duktape.value.object.DukFunction,
                    methodIdCache.at.renehollander.duktape.value.object.DukFunction.init,
                    duktape,
                    objectRef
            );
        } else if (duk_is_error(ctx, -1)) {
            retVal = env->NewObject(
                    classCache.at.renehollander.duktape.value.object.DukError,
                    methodIdCache.at.renehollander.duktape.value.object.DukError.init,
                    duktape,
                    objectRef
            );
        } else {
            retVal = env->NewObject(
                    classCache.at.renehollander.duktape.value.object.DukObject,
                    methodIdCache.at.renehollander.duktape.value.object.DukObject.init,
                    duktape,
                    objectRef
            );
        }
    } else {
        retVal = env->NewObject(
                classCache.at.renehollander.duktape.value.primitive.DukUndefined,
                methodIdCache.at.renehollander.duktape.value.primitive.DukUndefined.init,
                duktape
        );
    }
    duk_pop(ctx);
    return retVal;
}

void duj_java_object_to_value(JNIEnv *env, duk_context *ctx, jobject object) {
    if (env->IsInstanceOf(object, classCache.at.renehollander.duktape.value.primitive.DukNumber)) {
        duk_push_number(ctx, env->GetDoubleField(object, fieldIdCache.at.renehollander.duktape.value.primitive.DukNumber.value));
    } else if (env->IsInstanceOf(object, classCache.at.renehollander.duktape.value.primitive.DukBoolean)) {
        duk_push_boolean(ctx, env->GetBooleanField(object, fieldIdCache.at.renehollander.duktape.value.primitive.DukBoolean.value));
    } else if (env->IsInstanceOf(object, classCache.at.renehollander.duktape.value.primitive.DukString)) {
        jstring jValue = (jstring) env->GetObjectField(object, fieldIdCache.at.renehollander.duktape.value.primitive.DukString.value);
        const char *value = env->GetStringUTFChars(jValue, 0);
        duk_push_string(ctx, value);
        env->ReleaseStringUTFChars(jValue, value);
    } else if (env->IsInstanceOf(object, classCache.at.renehollander.duktape.value.primitive.DukUndefined)) {
        duk_push_undefined(ctx);
    } else if (env->IsInstanceOf(object, classCache.at.renehollander.duktape.value.primitive.DukNull)) {
        duk_push_null(ctx);
    } else if (env->IsInstanceOf(object, classCache.at.renehollander.duktape.value.object.DukArray)) {
        int ref = env->GetIntField(object, fieldIdCache.at.renehollander.duktape.value.object.DukArray.reference);
        duj_push_ref(ctx, ref);
    } else if (env->IsInstanceOf(object, classCache.at.renehollander.duktape.value.object.DukObject)) {
        int ref = env->GetIntField(object, fieldIdCache.at.renehollander.duktape.value.object.DukObject.reference);
        duj_push_ref(ctx, ref);
    } else if (env->IsInstanceOf(object, classCache.at.renehollander.duktape.value.object.AbstractDukReferencedValue)) {
        int ref = env->GetIntField(object, fieldIdCache.at.renehollander.duktape.value.object.AbstractDukReferencedValue.reference);
        duj_push_ref(ctx, ref);
    }
}