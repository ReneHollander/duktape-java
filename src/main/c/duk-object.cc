#include <iosfwd>
#include <sstream>
#include "duk-object.h"
#include "duktape.h"
#include "helper.h"
#include "cache.h"
#include "refs.h"

using namespace std;

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_values_DukObject_createEmptyObject(JNIEnv *env, jclass cls, jobject duktape) {
    duk_context *ctx = getContextFromObject(env, duktape);
    duk_push_object(ctx);
    return duj_ref(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putDouble(JNIEnv *env, jobject dukObject, jstring jKey, jdouble jValue) {
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_context *ctx = getContextFromDukValue(env, dukObject);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukObject));
    duk_push_number(ctx, jValue);
    duk_put_prop_string(ctx, -2, key);
    duk_pop(ctx);
    env->ReleaseStringUTFChars(jKey, key);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putBoolean(JNIEnv *env, jobject dukObject, jstring jKey, jboolean jValue) {
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_context *ctx = getContextFromDukValue(env, dukObject);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukObject));
    duk_push_boolean(ctx, jValue);
    duk_put_prop_string(ctx, -2, key);
    duk_pop(ctx);
    env->ReleaseStringUTFChars(jKey, key);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putString(JNIEnv *env, jobject dukObject, jstring jKey, jstring jValue) {
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_context *ctx = getContextFromDukValue(env, dukObject);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukObject));
    if (jValue != NULL) {
        const char *value = env->GetStringUTFChars(jValue, 0);
        duk_push_string(ctx, value);
        env->ReleaseStringUTFChars(jValue, value);
    } else {
        duk_push_null(ctx);
    }
    duk_put_prop_string(ctx, -2, key);
    duk_pop(ctx);
    env->ReleaseStringUTFChars(jKey, key);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putUndefined(JNIEnv *env, jobject dukObject, jstring jKey) {
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_context *ctx = getContextFromDukValue(env, dukObject);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukObject));
    duk_push_undefined(ctx);
    duk_put_prop_string(ctx, -2, key);
    duk_pop(ctx);
    env->ReleaseStringUTFChars(jKey, key);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putNull(JNIEnv *env, jobject dukObject, jstring jKey) {
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_context *ctx = getContextFromDukValue(env, dukObject);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukObject));
    duk_push_null(ctx);
    duk_put_prop_string(ctx, -2, key);
    duk_pop(ctx);
    env->ReleaseStringUTFChars(jKey, key);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putReference(JNIEnv *env, jobject dukObject, jstring jKey, jint jValue) {
    const char *key = env->GetStringUTFChars(jKey, 0);
    char hiddenName[strlen(key) + 2];
    strcpy(hiddenName, "\xff");
    strcat(hiddenName, key);
    duk_context *ctx = getContextFromDukValue(env, dukObject);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukObject));

    duj_push_ref(ctx, jValue);
    duk_put_prop_string(ctx, -2, key);

    duk_push_int(ctx, jValue);
    duk_put_prop_string(ctx, -2, hiddenName);

    duk_pop(ctx);
    env->ReleaseStringUTFChars(jKey, key);
}

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_values_DukObject_size(JNIEnv *env, jobject dukObject) {
    duk_context *ctx = getContextFromDukValue(env, dukObject);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukObject));
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

JNIEXPORT jboolean JNICALL Java_at_renehollander_duktape_values_DukObject__1containsKey(JNIEnv *env, jobject dukObject, jstring jKey) {
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_context *ctx = getContextFromDukValue(env, dukObject);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukObject));
    jboolean has = (jboolean) duk_has_prop_string(ctx, -1, key);
    duk_pop(ctx);
    env->ReleaseStringUTFChars(jKey, key);
    return has;
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1remove(JNIEnv *env, jobject dukObject, jstring jKey) {
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_context *ctx = getContextFromDukValue(env, dukObject);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukObject));
    duk_del_prop_string(ctx, -1, key);
    duk_pop(ctx);
    env->ReleaseStringUTFChars(jKey, key);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject_clear(JNIEnv *env, jobject dukObject) {
    duk_context *ctx = getContextFromDukValue(env, dukObject);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukObject));
    duk_enum(ctx, -1, 0);
    while (duk_next(ctx, -1, 0)) {
        duk_del_prop_string(ctx, -3, duk_get_string(ctx, -1));
        duk_pop(ctx);
    }
    duk_pop(ctx);
    duk_pop(ctx);
}

JNIEXPORT jstring JNICALL Java_at_renehollander_duktape_values_DukObject_toJSON(JNIEnv *env, jobject dukObject) {
    duk_context *ctx = getContextFromDukValue(env, dukObject);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukObject));
    const char *json = duk_json_encode(ctx, -1);
    duk_pop(ctx);
    return env->NewStringUTF(json);
}

JNIEXPORT jobject JNICALL Java_at_renehollander_duktape_values_DukObject__1get(JNIEnv *env, jobject dukObject, jstring jKey) {
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_context *ctx = getContextFromDukValue(env, dukObject);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukObject));

    duk_get_prop_string(ctx, -1, key);
    int type = duk_get_type(ctx, -1);
    jobject retVal = NULL;
    if (type == DUK_TYPE_NUMBER) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukNumber,
                methodIdCache.AtReneHollanderDuktapeValuesDukNumberInit,
                getParentDuktapeFromDukValue(env, dukObject),
                duk_get_number(ctx, -1)
        );
    } else if (type == DUK_TYPE_BOOLEAN) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukBoolean,
                methodIdCache.AtReneHollanderDuktapeValuesDukBooleanInit,
                getParentDuktapeFromDukValue(env, dukObject),
                duk_get_boolean(ctx, -1)
        );
    } else if (type == DUK_TYPE_STRING) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukString,
                methodIdCache.AtReneHollanderDuktapeValuesDukStringInit,
                getParentDuktapeFromDukValue(env, dukObject),
                env->NewStringUTF(duk_get_string(ctx, -1))
        );
    } else if (type == DUK_TYPE_UNDEFINED) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukUndefined,
                methodIdCache.AtReneHollanderDuktapeValuesDukUndefinedInit,
                getParentDuktapeFromDukValue(env, dukObject)
        );
    } else if (type == DUK_TYPE_NULL) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukNull,
                methodIdCache.AtReneHollanderDuktapeValuesDukNullInit,
                getParentDuktapeFromDukValue(env, dukObject)
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
                    getParentDuktapeFromDukValue(env, dukObject),
                    ref
            );
        } else if (duk_is_object(ctx, -1)) {
            retVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukObject,
                    methodIdCache.AtReneHollanderDuktapeValuesDukObjectInit,
                    getParentDuktapeFromDukValue(env, dukObject),
                    ref
            );
        } else if (duk_is_function(ctx, -1)) {
            retVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukFunction,
                    methodIdCache.AtReneHollanderDuktapeValuesDukFunctionInit,
                    getParentDuktapeFromDukValue(env, dukObject),
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
                getParentDuktapeFromDukValue(env, dukObject)
        );
    }
    return retVal;
}