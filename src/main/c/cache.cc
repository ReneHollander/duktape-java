#include "cache.h"
#include "helper.h"

ClassCache classCache;
MethodIDCache methodIdCache;
FieldIDCache fieldIdCache;

void populateCache() {
    JNIEnv *env = getJNIEnv();

    classCache.JavaLangObject = env->FindClass("java/lang/Object");
    classCache.JavaLangInteger = env->FindClass("java/lang/Integer");
    classCache.JavaLangLong = env->FindClass("java/lang/Long");
    classCache.JavaLangString = env->FindClass("java/lang/String");
    classCache.AtReneHollanderDuktapeDuktape = env->FindClass("at/renehollander/duktape/Duktape");
    classCache.AtReneHollanderDuktapeValuesDukValue = env->FindClass("at/renehollander/duktape/values/DukValue");
    classCache.AtReneHollanderDuktapeValuesDukReferencedValue = env->FindClass("at/renehollander/duktape/values/DukReferencedValue");
    classCache.AtReneHollanderDuktapeValuesDukArray = env->FindClass("at/renehollander/duktape/values/DukArray");
    classCache.AtReneHollanderDuktapeValuesDukFunction = env->FindClass("at/renehollander/duktape/values/DukFunction");
    classCache.AtReneHollanderDuktapeValuesDukNull = env->FindClass("at/renehollander/duktape/values/DukNull");
    classCache.AtReneHollanderDuktapeValuesDukNumber = env->FindClass("at/renehollander/duktape/values/DukNumber");
    classCache.AtReneHollanderDuktapeValuesDukObject = env->FindClass("at/renehollander/duktape/values/DukObject");
    classCache.AtReneHollanderDuktapeValuesDukString = env->FindClass("at/renehollander/duktape/values/DukString");
    classCache.AtReneHollanderDuktapeValuesDukUndefined = env->FindClass("at/renehollander/duktape/values/DukUndefined");
    classCache.AtReneHollanderDuktapeValuesDukBoolean = env->FindClass("at/renehollander/duktape/values/DukBoolean");

    methodIdCache.JavaLangIntegerInit = env->GetMethodID(classCache.JavaLangInteger, "<init>", "(I)V");
    methodIdCache.JavaLangLongInit = env->GetMethodID(classCache.JavaLangLong, "<init>", "(J)V");
    methodIdCache.AtReneHollanderDuktapeDuktapeFatalErrorHandler = env->GetMethodID(classCache.AtReneHollanderDuktapeDuktape, "fatalErrorHandler", "(ILjava/lang/String;)V");
    methodIdCache.AtReneHollanderDuktapeValuesDukArrayInit = env->GetMethodID(classCache.AtReneHollanderDuktapeValuesDukArray, "<init>", "(Lat/renehollander/duktape/Duktape;I)V");
    methodIdCache.AtReneHollanderDuktapeValuesDukFunctionInit = env->GetMethodID(classCache.AtReneHollanderDuktapeValuesDukFunction, "<init>", "(Lat/renehollander/duktape/Duktape;I)V");
    methodIdCache.AtReneHollanderDuktapeValuesDukNullInit = env->GetMethodID(classCache.AtReneHollanderDuktapeValuesDukNull, "<init>", "(Lat/renehollander/duktape/Duktape;)V");
    methodIdCache.AtReneHollanderDuktapeValuesDukNumberInit = env->GetMethodID(classCache.AtReneHollanderDuktapeValuesDukNumber, "<init>", "(Lat/renehollander/duktape/Duktape;D)V");
    methodIdCache.AtReneHollanderDuktapeValuesDukObjectInit = env->GetMethodID(classCache.AtReneHollanderDuktapeValuesDukObject, "<init>", "(Lat/renehollander/duktape/Duktape;I)V");
    methodIdCache.AtReneHollanderDuktapeValuesDukStringInit = env->GetMethodID(classCache.AtReneHollanderDuktapeValuesDukString, "<init>", "(Lat/renehollander/duktape/Duktape;Ljava/lang/String;)V");
    methodIdCache.AtReneHollanderDuktapeValuesDukUndefinedInit = env->GetMethodID(classCache.AtReneHollanderDuktapeValuesDukUndefined, "<init>", "(Lat/renehollander/duktape/Duktape;)V");
    methodIdCache.AtReneHollanderDuktapeValuesDukBooleanInit = env->GetMethodID(classCache.AtReneHollanderDuktapeValuesDukBoolean, "<init>", "(Lat/renehollander/duktape/Duktape;Z)V");
}