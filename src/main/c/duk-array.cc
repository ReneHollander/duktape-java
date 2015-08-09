#include <iosfwd>
#include <sstream>
#include "duk-array.h"
#include "duktape.h"
#include "cache.h"
#include "refs.h"

using namespace std;

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
        stringstream hiddenName;
        hiddenName << "\xff" << index;
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
    if (retVal == NULL) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukUndefined,
                methodIdCache.AtReneHollanderDuktapeValuesDukUndefinedInit,
                duktape
        );
    }
    return retVal;
}

/* ======================================================================== */
/* =========================== START add(value) =========================== */
/* ======================================================================== */

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addDouble(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jdouble value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_number(ctx, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addBoolean(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jboolean value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_boolean(ctx, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addString(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jstring jValue) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    const char *value = env->GetStringUTFChars(jValue, 0);
    duk_push_string(ctx, value);
    env->ReleaseStringUTFChars(jValue, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addUndefined(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_undefined(ctx);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addNull(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);
    duk_push_null(ctx);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) (duk_get_length(ctx, -2)));
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukArray__1addReference(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jint value) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);

    long newPos = duk_get_length(ctx, -1);

    stringstream hiddenName;
    hiddenName << "\xff" << newPos;

    duj_push_ref(ctx, value);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) newPos);

    duk_push_int(ctx, value);
    duk_put_prop_string(ctx, -2, hiddenName.str().c_str());

    duk_pop(ctx);
}

/* ======================================================================== */
/* =========================== END add(value) ============================= */
/* ======================================================================== */