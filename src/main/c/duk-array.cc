#include "duk-array.h"
#include "cache.h"
#include "refs.h"

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_values_DukArray__1createArray(JNIEnv *env, jclass cls, jlong contextPointer) {
    duk_context *ctx = (void *) contextPointer;
    duk_push_array(ctx);
    return duj_ref(ctx);
}

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_values_DukArray__1size(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    int size = (int) duk_get_length(ctx, -1);
    duk_pop(ctx);
    return size;
}

JNIEXPORT jstring JNICALL Java_at_renehollander_duktape_values_DukArray__1toJSON(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    const char *json = duk_json_encode(ctx, -1);
    duk_pop(ctx);
    return env->NewStringUTF(json);
}

JNIEXPORT jobject JNICALL Java_at_renehollander_duktape_values_DukArray__1get(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jobject duktape, jint index) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_get_prop_index(ctx, -1, (duk_uarridx_t) index);
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
        duk_dup(ctx, -1);
        int ref = duj_ref(ctx);

        if (duk_is_array(ctx, -1)) {
            retVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukArray,
                    methodIdCache.AtReneHollanderDuktapeValuesDukArrayInit,
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
        } else {
            retVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukObject,
                    methodIdCache.AtReneHollanderDuktapeValuesDukObjectInit,
                    duktape,
                    ref
            );
        }
    }

    duk_pop(ctx);
    duk_pop(ctx);
    if (retVal == NULL) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukUndefined,
                methodIdCache.AtReneHollanderDuktapeValuesDukUndefinedInit,
                duktape
        );
    }
    return retVal;
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1remove(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index) {
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

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addDouble__JID(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jdouble value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_number(ctx, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addBoolean__JIZ(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jboolean value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_boolean(ctx, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addString__JILjava_lang_String_2(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jValue) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    const char *value = env->GetStringUTFChars(jValue, 0);
    duk_push_string(ctx, value);
    env->ReleaseStringUTFChars(jValue, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addUndefined__JI(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_undefined(ctx);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addNull__JI(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_null(ctx);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addReference__JII(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint value) {
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

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addDouble__JIID(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index, jdouble value) {
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

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addBoolean__JIIZ(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index, jboolean value) {
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

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addString__JIILjava_lang_String_2(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index, jstring jValue) {
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

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addUndefined__JII(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index) {
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

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addNull__JII(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index) {
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

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addReference__JIII(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index, jint value) {
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

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1setDouble(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index, jdouble value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_number(ctx, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) index);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1setBoolean(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index, jboolean value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_boolean(ctx, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) index);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1setString(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index, jstring jValue) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    const char *value = env->GetStringUTFChars(jValue, 0);
    duk_push_string(ctx, value);
    env->ReleaseStringUTFChars(jValue, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) index);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1setUndefined(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_undefined(ctx);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) index);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1setNull(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_null(ctx);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) index);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1setReference(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint index, jint value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);

    duj_push_ref(ctx, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) index);

    duk_pop(ctx);
}

/* ======================================================================== */
/* ========================= END set(index value) ========================= */
/* ======================================================================== */