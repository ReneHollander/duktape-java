#include "cache.h"
#include "helper.h"

ClassCache classCache;
MethodIDCache methodIdCache;
FieldIDCache fieldIdCache;

void populateCache() {
    JNIEnv* env = getJNIEnv();
    classCache.JavaLangObject = env->FindClass("java/lang/Object");
    classCache.JavaLangInteger = env->FindClass("java/lang/Integer");
    classCache.JavaLangLong = env->FindClass("java/lang/Long");
    classCache.AtReneHollanderDuktapeDuktape = env->FindClass("at/renehollander/duktape/Duktape");
    classCache.AtReneHollanderDuktapeValuesDukValue = env->FindClass("at/renehollander/duktape/values/DukValue");
    classCache.AtReneHollanderDuktapeValuesDukArray = env->FindClass("at/renehollander/duktape/values/DukArray");
    classCache.AtReneHollanderDuktapeValuesDukFunction = env->FindClass("at/renehollander/duktape/values/DukFunction");
    classCache.AtReneHollanderDuktapeValuesDukNull = env->FindClass("at/renehollander/duktape/values/DukNull");
    classCache.AtReneHollanderDuktapeValuesDukNumber = env->FindClass("at/renehollander/duktape/values/DukNumber");
    classCache.AtReneHollanderDuktapeValuesDukObject = env->FindClass("at/renehollander/duktape/values/DukObject");
    classCache.AtReneHollanderDuktapeValuesDukReferencedValue = env->FindClass("at/renehollander/duktape/values/DukReferencedValue");
    classCache.AtReneHollanderDuktapeValuesDukString = env->FindClass("at/renehollander/duktape/values/DukString");
    classCache.AtReneHollanderDuktapeValuesDukUndefined = env->FindClass("at/renehollander/duktape/values/DukUndefined");
    classCache.AtReneHollanderDuktapeValuesDukBoolean = env->FindClass("at/renehollander/duktape/values/DukBoolean");

    methodIdCache.JavaLangIntegerInit = env->GetMethodID(classCache.JavaLangInteger, "<init>", "(I)V");
    methodIdCache.JavaLangLongInit = env->GetMethodID(classCache.JavaLangLong, "<init>", "(J)V");

    fieldIdCache.AtReneHollanderDuktapeDuktapeContextPtr = env->GetFieldID(classCache.AtReneHollanderDuktapeDuktape, "contextPtr", "J");
    fieldIdCache.AtReneHollanderDuktapeValuesDukValueParent = env->GetFieldID(classCache.AtReneHollanderDuktapeValuesDukValue, "parent", "Lat/renehollander/duktape/Duktape;");
    fieldIdCache.AtReneHollanderDuktapeValuesDukReferencedValueRef = env->GetFieldID(classCache.AtReneHollanderDuktapeValuesDukReferencedValue, "ref", "I");
    fieldIdCache.AtReneHollanderDuktapeValuesDukNumberValue = env->GetFieldID(classCache.AtReneHollanderDuktapeValuesDukNumber, "value", "D");
    fieldIdCache.AtReneHollanderDuktapeValuesDukStringValue = env->GetFieldID(classCache.AtReneHollanderDuktapeValuesDukString, "value", "Ljava/lang/String;");
    fieldIdCache.AtReneHollanderDuktapeValuesDukBooleanValue = env->GetFieldID(classCache.AtReneHollanderDuktapeValuesDukBoolean, "value", "Z");
}