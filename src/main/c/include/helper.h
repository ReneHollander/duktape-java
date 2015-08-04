#pragma once

#include "jni.h"

extern JavaVM *jvm;

JNIEnv* getJNIEnv();