#include "cache.h"
#include "helper.h"

ClassCache classCache;
MethodIDCache methodIdCache;
FieldIDCache fieldIdCache;

void populateCache() {
    JNIEnv *env = setupJNIEnv();

    classCache.JavaLangObject = (jclass) env->NewGlobalRef(env->FindClass("java/lang/Object"));
    classCache.JavaLangInteger = (jclass) env->NewGlobalRef(env->FindClass("java/lang/Integer"));
    classCache.JavaLangLong = (jclass) env->NewGlobalRef(env->FindClass("java/lang/Long"));
    classCache.JavaLangString = (jclass) env->NewGlobalRef(env->FindClass("java/lang/String"));
    classCache.AtReneHollanderDuktapeDuktape = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/Duktape"));
    classCache.AtReneHollanderDuktapeValuesDukValue = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/values/DukValue"));
    classCache.AtReneHollanderDuktapeValuesDukReferencedValue = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/values/DukReferencedValue"));
    classCache.AtReneHollanderDuktapeValuesAbstractDukValue = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/values/AbstractDukValue"));
    classCache.AtReneHollanderDuktapeValuesAbstractDukReferencedValue = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/values/AbstractDukReferencedValue"));
    classCache.AtReneHollanderDuktapeValuesDukError = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/values/DukError"));
    classCache.AtReneHollanderDuktapeValuesDukArray = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/values/DukArray"));
    classCache.AtReneHollanderDuktapeValuesDukFunction = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/values/DukFunction"));
    classCache.AtReneHollanderDuktapeValuesDukNull = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/values/DukNull"));
    classCache.AtReneHollanderDuktapeValuesDukNumber = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/values/DukNumber"));
    classCache.AtReneHollanderDuktapeValuesDukObject = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/values/DukObject"));
    classCache.AtReneHollanderDuktapeValuesDukString = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/values/DukString"));
    classCache.AtReneHollanderDuktapeValuesDukUndefined = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/values/DukUndefined"));
    classCache.AtReneHollanderDuktapeValuesDukBoolean = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/values/DukBoolean"));

    methodIdCache.JavaLangIntegerInit = env->GetMethodID(classCache.JavaLangInteger, "<init>", "(I)V");
    methodIdCache.JavaLangLongInit = env->GetMethodID(classCache.JavaLangLong, "<init>", "(J)V");
    methodIdCache.AtReneHollanderDuktapeDuktapeFatalErrorHandler = env->GetMethodID(classCache.AtReneHollanderDuktapeDuktape, "fatalErrorHandler", "(ILjava/lang/String;)V");
    methodIdCache.AtReneHollanderDuktapeValuesDukErrorCreateError = env->GetStaticMethodID(classCache.AtReneHollanderDuktapeValuesDukError, "createError", "(Lat/renehollander/duktape/Duktape;ILjava/lang/String;)Lat/renehollander/duktape/values/DukError;");
    methodIdCache.AtReneHollanderDuktapeValuesDukArrayInit = env->GetMethodID(classCache.AtReneHollanderDuktapeValuesDukArray, "<init>", "(Lat/renehollander/duktape/Duktape;I)V");
    methodIdCache.AtReneHollanderDuktapeValuesDukFunctionInit = env->GetMethodID(classCache.AtReneHollanderDuktapeValuesDukFunction, "<init>", "(Lat/renehollander/duktape/Duktape;I)V");
    methodIdCache.AtReneHollanderDuktapeValuesDukNullInit = env->GetMethodID(classCache.AtReneHollanderDuktapeValuesDukNull, "<init>", "(Lat/renehollander/duktape/Duktape;)V");
    methodIdCache.AtReneHollanderDuktapeValuesDukNumberInit = env->GetMethodID(classCache.AtReneHollanderDuktapeValuesDukNumber, "<init>", "(Lat/renehollander/duktape/Duktape;D)V");
    methodIdCache.AtReneHollanderDuktapeValuesDukObjectInit = env->GetMethodID(classCache.AtReneHollanderDuktapeValuesDukObject, "<init>", "(Lat/renehollander/duktape/Duktape;I)V");
    methodIdCache.AtReneHollanderDuktapeValuesDukStringInit = env->GetMethodID(classCache.AtReneHollanderDuktapeValuesDukString, "<init>", "(Lat/renehollander/duktape/Duktape;Ljava/lang/String;)V");
    methodIdCache.AtReneHollanderDuktapeValuesDukUndefinedInit = env->GetMethodID(classCache.AtReneHollanderDuktapeValuesDukUndefined, "<init>", "(Lat/renehollander/duktape/Duktape;)V");
    methodIdCache.AtReneHollanderDuktapeValuesDukBooleanInit = env->GetMethodID(classCache.AtReneHollanderDuktapeValuesDukBoolean, "<init>", "(Lat/renehollander/duktape/Duktape;Z)V");

    fieldIdCache.AtReneHollanderDuktapeValuesDukNumberValue = env->GetFieldID(classCache.AtReneHollanderDuktapeValuesDukNumber, "value", "D");
    fieldIdCache.AtReneHollanderDuktapeValuesDukBooleanValue = env->GetFieldID(classCache.AtReneHollanderDuktapeValuesDukBoolean, "value", "Z");
    fieldIdCache.AtReneHollanderDuktapeValuesDukStringValue = env->GetFieldID(classCache.AtReneHollanderDuktapeValuesDukString, "value", "Ljava/lang/String;");
    fieldIdCache.AtReneHollanderDuktapeValuesDukArrayReference = env->GetFieldID(classCache.AtReneHollanderDuktapeValuesDukArray, "ref", "I");
    fieldIdCache.AtReneHollanderDuktapeValuesDukObjectReference = env->GetFieldID(classCache.AtReneHollanderDuktapeValuesDukObject, "ref", "I");
    fieldIdCache.AtReneHollanderDuktapeValuesAbstractDukReferencedValueReference = env->GetFieldID(classCache.AtReneHollanderDuktapeValuesAbstractDukReferencedValue, "ref", "I");

    resetJNIEnv(env);
}