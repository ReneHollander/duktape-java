#pragma once

#include "jni.h"
#include "duktape.h"

extern JavaVM *jvm;

JNIEnv *getJNIEnv();

duk_context *getContextFromObject(JNIEnv *, jobject);

duk_context *getContextFromDukValue(JNIEnv *, jobject);

int getRefFromDukReferencedValue(JNIEnv *, jobject);

jobject getParentDuktapeFromDukValue(JNIEnv *, jobject);