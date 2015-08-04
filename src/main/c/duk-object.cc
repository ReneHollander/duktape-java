#include "duk-object.h"
#include "duktape.h"
#include "helper.h"
#include "cache.h"
#include "refs.h"

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
    duk_context *ctx = getContextFromDukValue(env, dukObject);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukObject));
    duj_push_ref(ctx, jValue);
    duk_put_prop_string(ctx, -2, key);
    duk_pop(ctx);
    env->ReleaseStringUTFChars(jKey, key);
}

JNIEXPORT jstring JNICALL Java_at_renehollander_duktape_values_DukObject_toJSON(JNIEnv *env, jobject dukObject) {
    duk_context *ctx = getContextFromDukValue(env, dukObject);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukObject));
    const char* json = duk_json_encode(ctx, -1);
    duk_pop(ctx);
    return env->NewStringUTF(json);
}