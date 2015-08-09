#pragma once

#include "jni.h"
#include "duktape.h"
#include "duktape_user_data.h"

extern JavaVM *jvm;

JNIEnv *getJNIEnv();

DuktapeUserData *getDuktapeUserData(duk_context *ctx);