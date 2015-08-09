#include <stdlib.h>
#include <duktape_user_data.h>

#include "helper.h"
#include "cache.h"

JavaVM *jvm = NULL;

JNIEnv *getJNIEnv() {
    JNIEnv *env;
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        printf("GetEnv failed.");
        exit(1);
    }
    return env;
}

duk_context *getContextFromObject(JNIEnv *env, jobject obj) {
    return (duk_context *) env->GetLongField(obj, fieldIdCache.AtReneHollanderDuktapeDuktapeContextPtr);
}

duk_context *getContextFromDukValue(JNIEnv *env, jobject dukValue) {
    return getContextFromObject(env, getParentDuktapeFromDukValue(env, dukValue));
}

jobject getParentDuktapeFromDukValue(JNIEnv *env, jobject dukValue) {
    return env->CallObjectMethod(dukValue, methodIdCache.AtReneHollanderDuktapeValuesDukValueGetParent);
}

jint getRefFromDukReferencedValue(JNIEnv *env, jobject obj) {
    return env->CallIntMethod(obj, methodIdCache.AtReneHollanderDuktapeValuesDukReferencedValueGetRef);
}

DuktapeUserData *getDuktapeUserData(duk_context *ctx) {
    duk_memory_functions functions;
    duk_get_memory_functions(ctx, &functions);
    return (DuktapeUserData *) functions.udata;
}