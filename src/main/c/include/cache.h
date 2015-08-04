#pragma once

#include "jni.h"

struct ClassCache {
    jclass JavaLangObject;
    jclass JavaLangInteger;
    jclass JavaLangLong;
    jclass AtReneHollanderDuktapeDuktape;
};
typedef struct ClassCache ClassCache;

struct MethodIDCache {
    jmethodID JavaLangIntegerInit;
    jmethodID JavaLangLongInit;
};
typedef struct MethodIDCache MethodIDCache;

struct FieldIDCache {
    jfieldID AtReneHollanderDuktapeDuktapeContextPtr;
};
typedef struct FieldIDCache FieldIDCache;

extern ClassCache classCache;
extern MethodIDCache methodIdCache;
extern FieldIDCache fieldIdCache;

void populateCache();