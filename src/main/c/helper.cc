#include <stdlib.h>

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
    return env->GetObjectField(dukValue, fieldIdCache.AtReneHollanderDuktapeValuesDukValueParent);
}

jint getRefFromDukReferencedValue(JNIEnv *env, jobject obj) {
    return env->GetIntField(obj, fieldIdCache.AtReneHollanderDuktapeValuesDukReferencedValueRef);
}