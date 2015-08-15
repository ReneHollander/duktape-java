#pragma once

#include "jni.h"

struct ClassCache {
    jclass JavaLangString;
    jclass AtReneHollanderDuktapeDuktape;
    jclass AtReneHollanderDuktapeValuesDukReferencedValue;
    jclass AtReneHollanderDuktapeValuesAbstractDukReferencedValue;
    jclass AtReneHollanderDuktapeValuesDukError;
    jclass AtReneHollanderDuktapeValuesDukBuffer;
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
    jmethodID AtReneHollanderDuktapeDuktapeFatalErrorHandler;
    jmethodID AtReneHollanderDuktapeValuesDukErrorInit;
    jmethodID AtReneHollanderDuktapeValuesDukBufferInit;
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
    jfieldID AtReneHollanderDuktapeValuesDukNumberValue;
    jfieldID AtReneHollanderDuktapeValuesDukBooleanValue;
    jfieldID AtReneHollanderDuktapeValuesDukStringValue;
    jfieldID AtReneHollanderDuktapeValuesDukArrayReference;
    jfieldID AtReneHollanderDuktapeValuesDukObjectReference;
    jfieldID AtReneHollanderDuktapeValuesAbstractDukReferencedValueReference;
};
typedef struct FieldIDCache FieldIDCache;

extern ClassCache classCache;
extern MethodIDCache methodIdCache;
extern FieldIDCache fieldIdCache;

void populateCache();