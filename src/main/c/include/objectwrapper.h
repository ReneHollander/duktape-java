#pragma once

#include "jni.h"
#include "helper.h"
#include "cache.h"

jobject wrapInteger(JNIEnv *, jint);

jobject wrapLong(JNIEnv *, jlong);
