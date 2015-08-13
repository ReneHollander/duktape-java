#pragma once

#include "jni.h"
#include "duktape.h"
#include "duk-user-data.h"

extern JavaVM *jvm;

JNIEnv *setupJNIEnv();

void resetJNIEnv(JNIEnv *env);

DuktapeUserData *getDuktapeUserData(duk_context *ctx);

jobject duj_value_to_java_object(JNIEnv *env, duk_context *ctx, jobject duktape);