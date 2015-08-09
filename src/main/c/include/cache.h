#pragma once

#include "jni.h"

struct ClassCache {
    jclass JavaLangObject;
    jclass JavaLangInteger;
    jclass JavaLangLong;
    jclass AtReneHollanderDuktapeDuktape;
    jclass AtReneHollanderDuktapeValuesDukValue;
    jclass AtReneHollanderDuktapeValuesDukReferencedValue;
    jclass AtReneHollanderDuktapeValuesDukArray;
    jclass AtReneHollanderDuktapeValuesDukFunction;
    jclass AtReneHollanderDuktapeValuesDukNull;
    jclass AtReneHollanderDuktapeValuesDukNumber;
    jclass AtReneHollanderDuktapeValuesDukObject;
    jclass AtReneHollanderDuktapeValuesDukString;
    jclass AtReneHollanderDuktapeValuesDukUndefined;
    jclass AtReneHollanderDuktapeValuesDukBoolean;
};
typedef struct ClassCache ClassCache;

struct MethodIDCache {
    jmethodID JavaLangIntegerInit;
    jmethodID JavaLangLongInit;
    jmethodID AtReneHollanderDuktapeDuktapeFatalErrorHandler;
    jmethodID AtReneHollanderDuktapeValuesDukArrayInit;
    jmethodID AtReneHollanderDuktapeValuesDukFunctionInit;
    jmethodID AtReneHollanderDuktapeValuesDukNullInit;
    jmethodID AtReneHollanderDuktapeValuesDukNumberInit;
    jmethodID AtReneHollanderDuktapeValuesDukObjectInit;
    jmethodID AtReneHollanderDuktapeValuesDukStringInit;
    jmethodID AtReneHollanderDuktapeValuesDukUndefinedInit;
    jmethodID AtReneHollanderDuktapeValuesDukBooleanInit;
};
typedef struct MethodIDCache MethodIDCache;

struct FieldIDCache {
    jfieldID AtReneHollanderDuktapeDuktapeContextPtr;
    jfieldID AtReneHollanderDuktapeValuesDukValueParent;
    jfieldID AtReneHollanderDuktapeValuesDukReferencedValueRef;
};
typedef struct FieldIDCache FieldIDCache;

extern ClassCache classCache;
extern MethodIDCache methodIdCache;
extern FieldIDCache fieldIdCache;

void populateCache();