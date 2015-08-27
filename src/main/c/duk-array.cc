#include "duk-array.h"
#include "refs.h"
#include "helper.h"

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_value_object_DukArray__1createArray(JNIEnv *env, jclass cls, jlong contextPointer) {
    duk_context *ctx = (void *) contextPointer;
    duk_push_array(ctx);
    return duj_ref(ctx);
}

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_value_object_DukArray__1size(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    int size = (int) duk_get_length(ctx, -1);
    duk_pop(ctx);
    return size;
}

JNIEXPORT jstring JNICALL Java_at_renehollander_duktape_value_object_DukArray__1toJSON(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    const char *json = duk_json_encode(ctx, -1);
    duk_pop(ctx);
    return env->NewStringUTF(json);
}

JNIEXPORT jobject JNICALL Java_at_renehollander_duktape_value_object_DukArray__1get(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_get_prop_index(ctx, -1, (duk_uarridx_t) index);
    jobject retVal = duj_value_to_java_object(env, ctx);
    duk_pop(ctx);
    return retVal;
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1remove(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);

    // Workaround thanks to fatcerberus for Duktape #266
    duj_push_ref(ctx, "Array.splice");
    duk_dup(ctx, -2);
    duk_push_int(ctx, index);
    duk_push_int(ctx, 1);
    duk_call_method(ctx, 2);
    duk_pop(ctx);

    duk_pop(ctx);
}

/* ======================================================================== */
/* =========================== START add(value) =========================== */
/* ======================================================================== */

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1addDouble__JID(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jdouble value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_number(ctx, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1addBoolean__JIZ(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jboolean value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_boolean(ctx, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1addString__JILjava_lang_String_2(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jValue) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    const char *value = env->GetStringUTFChars(jValue, 0);
    duk_push_string(ctx, value);
    env->ReleaseStringUTFChars(jValue, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1addUndefined__JI(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_undefined(ctx);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1addNull__JI(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_null(ctx);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1addReference__JII(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);

    duk_uarridx_t newPos = (duk_uarridx_t) duk_get_length(ctx, -1);

    duj_push_ref(ctx, value);
    duk_put_prop_index(ctx, -2, newPos);

    duk_pop(ctx);
}

/* ======================================================================== */
/* =========================== END add(value) ============================= */
/* ======================================================================== */

/* ======================================================================== */
/* ======================== START add(index value) ======================== */
/* ======================================================================== */

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1addDouble__JIID(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index, jdouble value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);

    // Workaround thanks to fatcerberus for Duktape #266
    duj_push_ref(ctx, "Array.splice");
    duk_dup(ctx, -2);
    duk_push_int(ctx, index);
    duk_push_int(ctx, 0);
    duk_push_number(ctx, value);
    duk_call_method(ctx, 3);
    duk_pop(ctx);

    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1addBoolean__JIIZ(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index, jboolean value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);

    // Workaround thanks to fatcerberus for Duktape #266
    duj_push_ref(ctx, "Array.splice");
    duk_dup(ctx, -2);
    duk_push_int(ctx, index);
    duk_push_int(ctx, 0);
    duk_push_boolean(ctx, value);
    duk_call_method(ctx, 3);
    duk_pop(ctx);

    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1addString__JIILjava_lang_String_2(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index, jstring jValue) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);

    // Workaround thanks to fatcerberus for Duktape #266
    duj_push_ref(ctx, "Array.splice");
    duk_dup(ctx, -2);
    duk_push_int(ctx, index);
    duk_push_int(ctx, 0);
    const char *value = env->GetStringUTFChars(jValue, 0);
    duk_push_string(ctx, value);
    env->ReleaseStringUTFChars(jValue, value);
    duk_call_method(ctx, 3);
    duk_pop(ctx);

    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1addUndefined__JII(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);

    // Workaround thanks to fatcerberus for Duktape #266
    duj_push_ref(ctx, "Array.splice");
    duk_dup(ctx, -2);
    duk_push_int(ctx, index);
    duk_push_int(ctx, 0);
    duk_push_undefined(ctx);
    duk_call_method(ctx, 3);
    duk_pop(ctx);

    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1addNull__JII(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);

    // Workaround thanks to fatcerberus for Duktape #266
    duk_get_prop_string(ctx, -1, "splice");
    duk_dup(ctx, -2);
    duk_push_int(ctx, index);
    duk_push_int(ctx, 0);
    duk_push_null(ctx);
    duk_call_method(ctx, 3);
    duk_pop(ctx);

    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1addReference__JIII(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index, jint value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);

    // Workaround thanks to fatcerberus for Duktape #266
    duk_get_prop_string(ctx, -1, "splice");
    duk_dup(ctx, -2);
    duk_push_int(ctx, index);
    duk_push_int(ctx, 0);
    duj_push_ref(ctx, value);
    duk_call_method(ctx, 3);
    duk_pop(ctx);

    duk_pop(ctx);
}

/* ======================================================================== */
/* ========================= END add(index value) ========================= */
/* ======================================================================== */

/* ======================================================================== */
/* ======================== START set(index value) ======================== */
/* ======================================================================== */

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1setDouble(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index, jdouble value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_number(ctx, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) index);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1setBoolean(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index, jboolean value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_boolean(ctx, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) index);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1setString(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index, jstring jValue) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    const char *value = env->GetStringUTFChars(jValue, 0);
    duk_push_string(ctx, value);
    env->ReleaseStringUTFChars(jValue, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) index);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1setUndefined(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_undefined(ctx);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) index);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1setNull(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_null(ctx);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) index);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_value_object_DukArray__1setReference(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index, jint value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);

    duj_push_ref(ctx, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) index);

    duk_pop(ctx);
}

/* ======================================================================== */
/* ========================= END set(index value) ========================= */
/* ======================================================================== */