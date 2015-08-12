#include <cache.h>
#include "duk-function.h"
#include "duktape.h"
#include "refs.h"

JNIEXPORT jobject JNICALL Java_at_renehollander_duktape_values_DukFunction__1invoke(JNIEnv *env, jclass cls, jlong contextPointer, jint objectRef, jobjectArray arguments) {
    duk_context *ctx = (void *) contextPointer;
    duj_push_ref(ctx, objectRef);

    jsize argc = env->GetArrayLength(arguments);

    for (int i = 0; i < argc; i++) {
        jobject argument = env->GetObjectArrayElement(arguments, i);
        if (env->IsInstanceOf(argument, classCache.AtReneHollanderDuktapeValuesDukNumber)) {
            duk_push_number(ctx, env->GetDoubleField(argument, fieldIdCache.AtReneHollanderDuktapeValuesDukNumberValue));
        } else if (env->IsInstanceOf(argument, classCache.AtReneHollanderDuktapeValuesDukBoolean)) {
            duk_push_boolean(ctx, env->GetBooleanField(argument, fieldIdCache.AtReneHollanderDuktapeValuesDukBooleanValue));
        } else if (env->IsInstanceOf(argument, classCache.AtReneHollanderDuktapeValuesDukString)) {
            jstring jValue = (jstring) env->GetObjectField(argument, fieldIdCache.AtReneHollanderDuktapeValuesDukStringValue);
            const char *value = env->GetStringUTFChars(jValue, 0);
            duk_push_string(ctx, value);
            env->ReleaseStringUTFChars(jValue, value);
        } else if (env->IsInstanceOf(argument, classCache.AtReneHollanderDuktapeValuesDukUndefined)) {
            duk_push_undefined(ctx);
        } else if (env->IsInstanceOf(argument, classCache.AtReneHollanderDuktapeValuesDukNull)) {
            duk_push_null(ctx);
        } else if (env->IsInstanceOf(argument, classCache.AtReneHollanderDuktapeValuesDukArray)) {
            int ref = env->GetIntField(argument, fieldIdCache.AtReneHollanderDuktapeValuesDukArrayReference);
            duj_push_ref(ctx, ref);
        } else if (env->IsInstanceOf(argument, classCache.AtReneHollanderDuktapeValuesDukObject)) {
            int ref = env->GetIntField(argument, fieldIdCache.AtReneHollanderDuktapeValuesDukObjectReference);
            duj_push_ref(ctx, ref);
        } else if (env->IsInstanceOf(argument, classCache.AtReneHollanderDuktapeValuesDukReferencedValue)) {
            int ref = env->GetIntField(argument, fieldIdCache.AtReneHollanderDuktapeValuesAbstractDukReferencedValueReference);
            duj_push_ref(ctx, ref);
        }
    }

    duk_call(ctx, argc);
    duk_pop(ctx);

    return NULL;
}