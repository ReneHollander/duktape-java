#include "cache.h"
#include "helper.h"

ClassCache classCache;
MethodIDCache methodIdCache;
FieldIDCache fieldIdCache;

void populateCache() {
    JNIEnv *env = setupJNIEnv();

    classCache.java.lang.String = (jclass) env->NewGlobalRef(env->FindClass("java/lang/String"));
    classCache.at.renehollander.duktape.Duktape = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/Duktape"));
    classCache.at.renehollander.duktape.value.object.DukReferencedValue = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/value/object/DukReferencedValue"));
    classCache.at.renehollander.duktape.value.object.AbstractDukReferencedValue = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/value/object/AbstractDukReferencedValue"));
    classCache.at.renehollander.duktape.value.object.DukError = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/value/object/DukError"));
    classCache.at.renehollander.duktape.value.object.DukBuffer = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/value/object/DukBuffer"));
    classCache.at.renehollander.duktape.value.object.DukArray = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/value/object/DukArray"));
    classCache.at.renehollander.duktape.value.object.DukFunction = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/value/object/DukFunction"));
    classCache.at.renehollander.duktape.value.object.DukObject = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/value/object/DukObject"));
    classCache.at.renehollander.duktape.value.primitive.DukNull = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/value/primitive/DukNull"));
    classCache.at.renehollander.duktape.value.primitive.DukNumber = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/value/primitive/DukNumber"));
    classCache.at.renehollander.duktape.value.primitive.DukString = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/value/primitive/DukString"));
    classCache.at.renehollander.duktape.value.primitive.DukUndefined = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/value/primitive/DukUndefined"));
    classCache.at.renehollander.duktape.value.primitive.DukBoolean = (jclass) env->NewGlobalRef(env->FindClass("at/renehollander/duktape/value/primitive/DukBoolean"));

    methodIdCache.at.renehollander.duktape.Duktape.fatalErrorHandler = env->GetMethodID(classCache.at.renehollander.duktape.Duktape, "fatalErrorHandler", "(ILjava/lang/String;)V");
    methodIdCache.at.renehollander.duktape.value.object.DukError.init = env->GetMethodID(classCache.at.renehollander.duktape.value.object.DukError, "<init>", "(Lat/renehollander/duktape/Duktape;I)V");
    methodIdCache.at.renehollander.duktape.value.object.DukBuffer.init = env->GetMethodID(classCache.at.renehollander.duktape.value.object.DukBuffer, "<init>", "(Lat/renehollander/duktape/Duktape;I)V");
    methodIdCache.at.renehollander.duktape.value.object.DukArray.init = env->GetMethodID(classCache.at.renehollander.duktape.value.object.DukArray, "<init>", "(Lat/renehollander/duktape/Duktape;I)V");
    methodIdCache.at.renehollander.duktape.value.object.DukFunction.init = env->GetMethodID(classCache.at.renehollander.duktape.value.object.DukFunction, "<init>", "(Lat/renehollander/duktape/Duktape;I)V");
    methodIdCache.at.renehollander.duktape.value.object.DukObject.init = env->GetMethodID(classCache.at.renehollander.duktape.value.object.DukObject, "<init>", "(Lat/renehollander/duktape/Duktape;I)V");
    methodIdCache.at.renehollander.duktape.value.primitive.DukNull.init = env->GetMethodID(classCache.at.renehollander.duktape.value.primitive.DukNull, "<init>", "(Lat/renehollander/duktape/Duktape;)V");
    methodIdCache.at.renehollander.duktape.value.primitive.DukNumber.init = env->GetMethodID(classCache.at.renehollander.duktape.value.primitive.DukNumber, "<init>", "(Lat/renehollander/duktape/Duktape;D)V");
    methodIdCache.at.renehollander.duktape.value.primitive.DukString.init = env->GetMethodID(classCache.at.renehollander.duktape.value.primitive.DukString, "<init>", "(Lat/renehollander/duktape/Duktape;Ljava/lang/String;)V");
    methodIdCache.at.renehollander.duktape.value.primitive.DukUndefined.init = env->GetMethodID(classCache.at.renehollander.duktape.value.primitive.DukUndefined, "<init>", "(Lat/renehollander/duktape/Duktape;)V");
    methodIdCache.at.renehollander.duktape.value.primitive.DukBoolean.init = env->GetMethodID(classCache.at.renehollander.duktape.value.primitive.DukBoolean, "<init>", "(Lat/renehollander/duktape/Duktape;Z)V");

    fieldIdCache.at.renehollander.duktape.value.primitive.DukNumber.value = env->GetFieldID(classCache.at.renehollander.duktape.value.primitive.DukNumber, "value", "D");
    fieldIdCache.at.renehollander.duktape.value.primitive.DukBoolean.value = env->GetFieldID(classCache.at.renehollander.duktape.value.primitive.DukBoolean, "value", "Z");
    fieldIdCache.at.renehollander.duktape.value.primitive.DukString.value = env->GetFieldID(classCache.at.renehollander.duktape.value.primitive.DukString, "value", "Ljava/lang/String;");
    fieldIdCache.at.renehollander.duktape.value.object.DukArray.reference = env->GetFieldID(classCache.at.renehollander.duktape.value.object.DukArray, "ref", "I");
    fieldIdCache.at.renehollander.duktape.value.object.DukObject.reference = env->GetFieldID(classCache.at.renehollander.duktape.value.object.DukObject, "ref", "I");
    fieldIdCache.at.renehollander.duktape.value.object.AbstractDukReferencedValue.reference = env->GetFieldID(classCache.at.renehollander.duktape.value.object.AbstractDukReferencedValue, "ref", "I");

    resetJNIEnv(env);
}