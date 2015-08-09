#pragma once

#include "jni.h"
#include "duktape.h"
#include "duktape_user_data.h"

extern JavaVM *jvm;

JNIEnv *getJNIEnv();

duk_context *getContextFromObject(JNIEnv *, jobject);

duk_context *getContextFromDukValue(JNIEnv *, jobject);

int getRefFromDukReferencedValue(JNIEnv *, jobject);

jobject getParentDuktapeFromDukValue(JNIEnv *, jobject);

DuktapeUserData *getDuktapeUserData(duk_context *ctx);