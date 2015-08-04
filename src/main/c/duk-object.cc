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

JNIEXPORT jobject JNICALL Java_at_renehollander_duktape_values_DukObject_put(JNIEnv *env, jobject dukObject, jstring jName, jobject jValue) {
    duk_context *ctx = getContextFromDukValue(env, dukObject);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukObject));
    const char *name = env->GetStringUTFChars(jName, 0);

    if (env->IsInstanceOf(jValue, classCache.AtReneHollanderDuktapeValuesDukNumber)) {
        duk_push_number(ctx, env->GetDoubleField(jValue, fieldIdCache.AtReneHollanderDuktapeValuesDukNumberValue));
    } else if (env->IsInstanceOf(jValue, classCache.AtReneHollanderDuktapeValuesDukNull)) {
        duk_push_null(ctx);
    } else if (env->IsInstanceOf(jValue, classCache.AtReneHollanderDuktapeValuesDukUndefined)) {
        duk_push_undefined(ctx);
    } else if (env->IsInstanceOf(jValue, classCache.AtReneHollanderDuktapeValuesDukBoolean)) {
        bool value = env->GetBooleanField(jValue, fieldIdCache.AtReneHollanderDuktapeValuesDukBooleanValue);
        duk_push_boolean(ctx, value);
    } else if (env->IsInstanceOf(jValue, classCache.AtReneHollanderDuktapeValuesDukString)) {
        jstring jStringValue = (jstring) env->GetObjectField(jValue, fieldIdCache.AtReneHollanderDuktapeValuesDukStringValue);
        if (jStringValue == 0) {
            duk_push_null(ctx);
        } else {
            const char *stringValue = env->GetStringUTFChars(jStringValue, 0);
            duk_push_string(ctx, stringValue);
            env->ReleaseStringUTFChars(jStringValue, stringValue);
        }
    } else if (env->IsInstanceOf(jValue, classCache.AtReneHollanderDuktapeValuesDukReferencedValue)) {
        int valueRef = getRefFromDukReferencedValue(env, jValue);
        duj_push_ref(ctx, valueRef);
    } else {
        fprintf(stderr, "unknown type");
        exit(1);
    }

    duk_put_prop_string(ctx, -2, name);
    duk_pop(ctx);

    env->ReleaseStringUTFChars(jName, name);
}

JNIEXPORT jstring JNICALL Java_at_renehollander_duktape_values_DukObject_toJSON(JNIEnv *env, jobject dukObject) {
    duk_context *ctx = getContextFromDukValue(env, dukObject);
    duj_push_ref(ctx, getRefFromDukReferencedValue(env, dukObject));
    const char* json = duk_json_encode(ctx, -1);
    duk_pop(ctx);
    return env->NewStringUTF(json);
}