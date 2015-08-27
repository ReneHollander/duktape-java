#include "duk-object.h"
#include "cache.h"
#include "refs.h"
#include "helper.h"

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_value_object_DukObject_createObject(JNIEnv *env, jclass cls, jlong contextPointer) {
    duk_context *ctx = (void *) contextPointer;
    duk_push_object(ctx);
    return duj_ref(ctx);
}

static int getObjectSize(duk_context *ctx, duk_idx_t index) {
    int count = 0;
    duk_enum(ctx, index, 0);
    while (duk_next(ctx, -1, 0)) {
        count++;
        duk_pop(ctx);
    }
    duk_pop(ctx);
    return count;
}

JNIEXPORT jobjectArray JNICALL Java_at_renehollander_duktape_value_object_DukObject__1getKeys(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    int size = getObjectSize(ctx, -1);

    jobjectArray ret = (jobjectArray) env->NewObjectArray(size, classCache.java.lang.String, env->NewStringUTF(""));
    duk_enum(ctx, -1, 0);
    int count = 0;
    while (duk_next(ctx, -1, 0)) {
        env->SetObjectArrayElement(ret, count, env->NewStringUTF(duk_get_string(ctx, -1)));
        duk_pop(ctx);
        count++;
    }
    duk_pop(ctx);
    duk_pop(ctx);
    return ret;
}

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_value_object_DukObject__1size(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    int size = getObjectSize(ctx, -1);
    duk_pop(ctx);
    return size;
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukObject__1clear(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
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

JNIEXPORT jstring JNICALL Java_at_renehollander_duktape_value_object_DukObject__1toJSON(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    const char *json = duk_json_encode(ctx, -1);
    duk_pop(ctx);
    return env->NewStringUTF(json);
}

JNIEXPORT jboolean JNICALL Java_at_renehollander_duktape_value_object_DukObject__1containsKey(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jKey) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    const char *key = env->GetStringUTFChars(jKey, 0);
    jboolean has = (jboolean) duk_has_prop_string(ctx, -1, key);
    env->ReleaseStringUTFChars(jKey, key);
    duk_pop(ctx);
    return has;
}

JNIEXPORT jobject JNICALL Java_at_renehollander_duktape_value_object_DukObject__1get(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jKey) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_get_prop_string(ctx, -1, key);
    jobject retVal = duj_value_to_java_object(env, ctx);
    duk_pop(ctx);
    env->ReleaseStringUTFChars(jKey, key);
    return retVal;
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukObject__1remove(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jKey) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_del_prop_string(ctx, -1, key);
    env->ReleaseStringUTFChars(jKey, key);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukObject__1putDouble(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jKey, jdouble value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_number(ctx, value);
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_put_prop_string(ctx, -2, key);
    env->ReleaseStringUTFChars(jKey, key);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukObject__1putBoolean(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jKey, jboolean value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_boolean(ctx, value);
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_put_prop_string(ctx, -2, key);
    env->ReleaseStringUTFChars(jKey, key);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukObject__1putString(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jKey, jstring jValue) {
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

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukObject__1putUndefined(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jKey) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_undefined(ctx);
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_put_prop_string(ctx, -2, key);
    env->ReleaseStringUTFChars(jKey, key);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukObject__1putNull(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jKey) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_null(ctx);
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_put_prop_string(ctx, -2, key);
    env->ReleaseStringUTFChars(jKey, key);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukObject__1putReference(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jKey, jint value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duj_push_ref(ctx, value);
    const char *key = env->GetStringUTFChars(jKey, 0);
    duk_put_prop_string(ctx, -2, key);
    env->ReleaseStringUTFChars(jKey, key);
    duk_pop(ctx);
}