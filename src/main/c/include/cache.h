#pragma once

#include "jni.h"

struct ClassCache {
    jclass JavaLangObject;
    jclass JavaLangInteger;
    jclass JavaLangLong;
    jclass AtReneHollanderDuktapeDuktape;
    jclass AtReneHollanderDuktapeValuesDukValue;
    jclass AtReneHollanderDuktapeValuesDukArray;
    jclass AtReneHollanderDuktapeValuesDukFunction;
    jclass AtReneHollanderDuktapeValuesDukNull;
    jclass AtReneHollanderDuktapeValuesDukNumber;
    jclass AtReneHollanderDuktapeValuesDukObject;
    jclass AtReneHollanderDuktapeValuesDukReferencedValue;
    jclass AtReneHollanderDuktapeValuesDukString;
    jclass AtReneHollanderDuktapeValuesDukUndefined;
    jclass AtReneHollanderDuktapeValuesDukBoolean;
};
typedef struct ClassCache ClassCache;

struct MethodIDCache {
    jmethodID JavaLangIntegerInit;
    jmethodID JavaLangLongInit;
};
typedef struct MethodIDCache MethodIDCache;

struct FieldIDCache {
    jfieldID AtReneHollanderDuktapeDuktapeContextPtr;
    jfieldID AtReneHollanderDuktapeValuesDukValueParent;
    jfieldID AtReneHollanderDuktapeValuesDukReferencedValueRef;
    jfieldID AtReneHollanderDuktapeValuesDukNumberValue;
    jfieldID AtReneHollanderDuktapeValuesDukStringValue;
    jfieldID AtReneHollanderDuktapeValuesDukBooleanValue;
};
typedef struct FieldIDCache FieldIDCache;

extern ClassCache classCache;
extern MethodIDCache methodIdCache;
extern FieldIDCache fieldIdCache;

void populateCache();