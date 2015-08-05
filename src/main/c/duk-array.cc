#include "duk-array.h"
#include "duktape.h"
#include "helper.h"
#include "cache.h"
#include "refs.h"

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_values_DukArray_createEmptyArray(JNIEnv *env, jclass cls, jobject duktape) {
    duk_context *ctx = getContextFromObject(env, duktape);
    duk_push_array(ctx);
    return duj_ref(ctx);
}

JNIEXPORT jstring JNICALL Java_at_renehollander_duktape_values_DukArray_toJSON(JNIEnv *env, jobject dukArray) {
    duk_context *ctx = getContextFromDukValue(env, dukArray);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukArray));
    const char *json = duk_json_encode(ctx, -1);
    duk_pop(ctx);
    return env->NewStringUTF(json);
}


JNIEXPORT jint JNICALL Java_at_renehollander_duktape_values_DukArray_size(JNIEnv *env, jobject dukArray) {
    duk_context *ctx = getContextFromDukValue(env, dukArray);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukArray));
    int size = (int) duk_get_length(ctx, -1);
    duk_pop(ctx);
    return size;
}

/* ======================================================================== */
/* =========================== START add(value) =========================== */
/* ======================================================================== */

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addDouble(JNIEnv *env, jobject dukArray, jdouble jValue) {
    duk_context *ctx = getContextFromDukValue(env, dukArray);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukArray));
    duk_push_number(ctx, jValue);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addBoolean(JNIEnv *env, jobject dukArray, jboolean jValue) {
    duk_context *ctx = getContextFromDukValue(env, dukArray);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukArray));
    duk_push_boolean(ctx, jValue);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addString(JNIEnv *env, jobject dukArray, jstring jValue) {
    const char *value = env->GetStringUTFChars(jValue, 0);
    duk_context *ctx = getContextFromDukValue(env, dukArray);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukArray));
    duk_push_string(ctx, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
    env->ReleaseStringUTFChars(jValue, value);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addUndefined(JNIEnv *env, jobject dukArray) {
    duk_context *ctx = getContextFromDukValue(env, dukArray);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukArray));
    duk_push_undefined(ctx);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addNull(JNIEnv *env, jobject dukArray) {
    duk_context *ctx = getContextFromDukValue(env, dukArray);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukArray));
    duk_push_null(ctx);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addReference(JNIEnv *env, jobject dukArray, jint jValue) {
    char key[15];
    sprintf(key, "%d", jValue);
    char hiddenName[strlen(key) + 2];
    strcpy(hiddenName, "\xff");
    strcat(hiddenName, key);

    duk_context *ctx = getContextFromDukValue(env, dukArray);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukArray));
    
    duj_push_ref(ctx, jValue);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));

    duk_push_int(ctx, jValue);
    duk_put_prop_string(ctx, -2, hiddenName);

    duk_pop(ctx);
}

/* ======================================================================== */
/* =========================== END add(value) ============================= */
/* ======================================================================== */
