#include <iosfwd>
#include <sstream>
#include <iostream>
#include "duk-array.h"
#include "duktape.h"
#include "helper.h"
#include "cache.h"
#include "refs.h"

using namespace std;

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

JNIEXPORT jobject JNICALL Java_at_renehollander_duktape_values_DukArray_get(JNIEnv *env, jobject dukArray, jint index) {
    duk_context *ctx = getContextFromDukValue(env, dukArray);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukArray));
    duk_get_prop_index(ctx, -1, (duk_uarridx_t) index);
    int type = duk_get_type(ctx, -1);
    jobject retVal = NULL;
    if (type == DUK_TYPE_NUMBER) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukNumber,
                methodIdCache.AtReneHollanderDuktapeValuesDukNumberInit,
                getParentDuktapeFromDukValue(env, dukArray),
                duk_get_number(ctx, -1)
        );
    } else if (type == DUK_TYPE_BOOLEAN) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukBoolean,
                methodIdCache.AtReneHollanderDuktapeValuesDukBooleanInit,
                getParentDuktapeFromDukValue(env, dukArray),
                duk_get_boolean(ctx, -1)
        );
    } else if (type == DUK_TYPE_STRING) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukString,
                methodIdCache.AtReneHollanderDuktapeValuesDukStringInit,
                getParentDuktapeFromDukValue(env, dukArray),
                env->NewStringUTF(duk_get_string(ctx, -1))
        );
    } else if (type == DUK_TYPE_UNDEFINED) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukUndefined,
                methodIdCache.AtReneHollanderDuktapeValuesDukUndefinedInit,
                getParentDuktapeFromDukValue(env, dukArray)
        );
    } else if (type == DUK_TYPE_NULL) {
        retVal = env->NewObject(
                classCache.AtReneHollanderDuktapeValuesDukNull,
                methodIdCache.AtReneHollanderDuktapeValuesDukNullInit,
                getParentDuktapeFromDukValue(env, dukArray)
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
                    getParentDuktapeFromDukValue(env, dukArray),
                    ref
            );
        } else if (duk_is_object(ctx, -1)) {
            retVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukObject,
                    methodIdCache.AtReneHollanderDuktapeValuesDukObjectInit,
                    getParentDuktapeFromDukValue(env, dukArray),
                    ref
            );
        } else if (duk_is_function(ctx, -1)) {
            retVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukFunction,
                    methodIdCache.AtReneHollanderDuktapeValuesDukFunctionInit,
                    getParentDuktapeFromDukValue(env, dukArray),
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
                getParentDuktapeFromDukValue(env, dukArray)
        );
    }
    return retVal;
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
    duk_context *ctx = getContextFromDukValue(env, dukArray);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukArray));

    long newPos = duk_get_length(ctx, -1);

    stringstream hiddenName;
    hiddenName << "\xff" << newPos;

    duj_push_ref(ctx, jValue);
    duk_put_prop_index(ctx, -2, (duk_uarridx_t) newPos);

    duk_push_int(ctx, jValue);
    duk_put_prop_string(ctx, -2, hiddenName.str().c_str());

    duk_pop(ctx);
}

/* ======================================================================== */
/* =========================== END add(value) ============================= */
/* ======================================================================== */
