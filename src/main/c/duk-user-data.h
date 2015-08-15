#pragma once

#include "duk-memory-allocator.h"
#include "jni.h"
#include <vector>
#include <string>

struct DuktapeUserData {
    MemoryInfo memoryInfo;
    jobject duktape;
    struct UnrefData {
        std::vector<int> *mark_for_unref_indexed;
        std::vector<std::string> *mark_for_unref_named;
    } unrefData;
};

typedef struct DuktapeUserData DuktapeUserData;

