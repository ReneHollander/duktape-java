#pragma once

#include "memoryinfo.h"
#include "jni.h"

struct DuktapeUserData {
    MemoryInfo memoryInfo;
    jobject duktape;
};

typedef struct DuktapeUserData DuktapeUserData;