#pragma once

#include "jni.h"

struct MethodData {
    jobject callerObject;
    jmethodID methodID;
};
typedef struct MethodData MethodData;