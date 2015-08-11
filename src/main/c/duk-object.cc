#include <iosfwd>
#include <sstream>
#include "duk-object.h"
#include "cache.h"
#include "refs.h"

using namespace std;

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_values_DukObject_createObject(JNIEnv *env, jclass cls, jlong contextPointer) {
    duk_context *ctx = (void *) contextPointer;
    duk_push_object(ctx);
    return duj_ref(ctx);
}

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_values_DukObject__1size(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    int count = 0;
    duk_enum(ctx, -1, 0);
    while (duk_next(ctx, -1, 0)) {
        count++;
        duk_pop(ctx);
    }
    duk_pop(ctx);
    duk_pop(ctx);
    return count;
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1clear(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_enum(ctx, -1, 0);
    while (duk_next(ctx, -1, 0)) {
        duk_del_prop_string(ctx, -3, duk_get_string(ctx, -1));
        duk_pop(ctx);
    }
    duk_pop(ctx);
    duk_pop(ctx);
}

JNIEXPORT jstring JNICALL Java_at_renehollander_duktape_values_DukObject__1toJSON(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    const char *json = duk_json_encode(ctx, -1);
    duk_pop(ctx);
    return env->NewStringUTF(json);
}

JNIEXPORT jboolean JNICALL Java_at_renehollander_duktape_values_DukObject__1containsKey(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jKey) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    const char *key = env->GetStringUTFChars(jKey, 0);
    jboolean has = (jboolean) duk_has_prop_string(ctx, -1, key);
    env->ReleaseStringUTFChars(jKey, key);
    duk_pop(ctx);
    return has;
}

JNIEXPORT jobject JNICALL Java_at_renehollander_duktape_values_DukObject__1get(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jobject duktape, jstring jKey) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_get_prop_string(ctx, -1, key);
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
    } else if (type == DUK_TYPE_UNDEFINED) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukUndefined,
                methodIdCache.AtReneHollanderDuktapeValuesDukUndefinedInit,
                duktape
        );
    } else if (type == DUK_TYPE_NULL) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukNull,
                methodIdCache.AtReneHollanderDuktapeValuesDukNullInit,
                duktape
        );
    } else if (type == DUK_TYPE_OBJECT) {
        stringstream hiddenName;
        hiddenName << "\xff" << key;
        duk_get_prop_string(ctx, -2, hiddenName.str().c_str());
        int ref = duk_get_int(ctx, -1);
        duk_pop(ctx);

        if (duk_is_array(ctx, -1)) {
            retVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukArray,
                    methodIdCache.AtReneHollanderDuktapeValuesDukArrayInit,
                    duktape,
                    ref
            );
        } else if (duk_is_object(ctx, -1)) {
            retVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukObject,
                    methodIdCache.AtReneHollanderDuktapeValuesDukObjectInit,
                    duktape,
                    ref
            );
        } else if (duk_is_function(ctx, -1)) {
            retVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukFunction,
                    methodIdCache.AtReneHollanderDuktapeValuesDukFunctionInit,
                    duktape,
                    ref
            );
        }
    };

    duk_pop(ctx);
    duk_pop(ctx);
    env->ReleaseStringUTFChars(jKey, key);
    if (retVal == NULL) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukUndefined,
                methodIdCache.AtReneHollanderDuktapeValuesDukUndefinedInit,
                duktape
        );
    }
    return retVal;
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1remove(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jKey) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_del_prop_string(ctx, -1, key);
    env->ReleaseStringUTFChars(jKey, key);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putDouble(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jKey, jdouble value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_number(ctx, value);
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_put_prop_string(ctx, -2, key);
    env->ReleaseStringUTFChars(jKey, key);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putBoolean(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jKey, jboolean value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_boolean(ctx, value);
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_put_prop_string(ctx, -2, key);
    env->ReleaseStringUTFChars(jKey, key);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putString(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jKey, jstring jValue) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    if (jValue != NULL) {
        const char *value = env->GetStringUTFChars(jValue, 0);
        duk_push_string(ctx, value);
        env->ReleaseStringUTFChars(jValue, value);
    } else {
        duk_push_null(ctx);
    }
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_put_prop_string(ctx, -2, key);
    env->ReleaseStringUTFChars(jKey, key);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putUndefined(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jKey) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_undefined(ctx);
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_put_prop_string(ctx, -2, key);
    env->ReleaseStringUTFChars(jKey, key);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putNull(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jKey) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_null(ctx);
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_put_prop_string(ctx, -2, key);
    env->ReleaseStringUTFChars(jKey, key);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putReference(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jKey, jint value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);

    const char *key = env->GetStringUTFChars(jKey, 0);
    stringstream hiddenName;
    hiddenName << "\xff" << key;

    duj_push_ref(ctx, value);
    duk_put_prop_string(ctx, -2, key);

    duk_push_int(ctx, value);
    duk_put_prop_string(ctx, -2, hiddenName.str().c_str());

    duk_pop(ctx);
    env->ReleaseStringUTFChars(jKey, key);
}