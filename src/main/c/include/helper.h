#pragma once

#include "jni.h"
#include "duktape.h"
#include "duktape_user_data.h"

extern JavaVM *jvm;

JNIEnv *setupJNIEnv();

void resetJNIEnv(JNIEnv *env);

DuktapeUserData *getDuktapeUserData(duk_context *ctx);