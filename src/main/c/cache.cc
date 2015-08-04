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

    methodIdCache.JavaLangIntegerInit = env->GetMethodID(classCache.JavaLangInteger, "<init>", "(I)V");
    methodIdCache.JavaLangLongInit = env->GetMethodID(classCache.JavaLangLong, "<init>", "(J)V");

    fieldIdCache.AtReneHollanderDuktapeDuktapeContextPtr = env->GetFieldID(classCache.AtReneHollanderDuktapeDuktape, "contextPtr", "J");
}