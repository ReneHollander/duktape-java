#include "duk-java-function.h"
#include "duktape.h"
#include "refs.h"
#include "method.h"
#include "cache.h"
#include "helper.h"

int methodExecutor(duk_context *ctx) {
    JNIEnv *env = setupJNIEnv();
    DuktapeUserData *userData = getDuktapeUserData(ctx);

    duk_push_current_function(ctx);
    duk_get_prop_index(ctx, -1, 0);
    int ref = duk_get_int(ctx, -1);
    duk_pop(ctx);
    duk_pop(ctx);

    duk_size_t size;
    duj_push_ref(ctx, ref);
    MethodData *methodData = (MethodData *) duk_get_buffer(ctx, -1, &size);
    duk_pop(ctx);

    int argc = duk_get_top(ctx);
    jvalue args[argc];
    for (int i = 0; i < argc; i++) {
        int type = duk_get_type(ctx, -1);
        jobject argVal = NULL;
        if (type == DUK_TYPE_NUMBER) {
            argVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukNumber,
                    methodIdCache.AtReneHollanderDuktapeValuesDukNumberInit,
                    userData->duktape,
                    duk_get_number(ctx, -1)
            );
        } else if (type == DUK_TYPE_BOOLEAN) {
            argVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukBoolean,
                    methodIdCache.AtReneHollanderDuktapeValuesDukBooleanInit,
                    userData->duktape,
                    duk_get_boolean(ctx, -1)
            );
        } else if (type == DUK_TYPE_STRING) {
            argVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukString,
                    methodIdCache.AtReneHollanderDuktapeValuesDukStringInit,
                    userData->duktape,
                    env->NewStringUTF(duk_get_string(ctx, -1))
            );
        } else if (type == DUK_TYPE_UNDEFINED) {
            argVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukUndefined,
                    methodIdCache.AtReneHollanderDuktapeValuesDukUndefinedInit,
                    userData->duktape
            );
        } else if (type == DUK_TYPE_NULL) {
            argVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukNull,
                    methodIdCache.AtReneHollanderDuktapeValuesDukNullInit,
                    userData->duktape
            );
        } else if (type == DUK_TYPE_OBJECT) {
            duk_dup(ctx, -1);
            int objectRef = duj_ref(ctx);

            if (duk_is_array(ctx, -1)) {
                argVal = env->NewObject(
                        classCache.AtReneHollanderDuktapeValuesDukArray,
                        methodIdCache.AtReneHollanderDuktapeValuesDukArrayInit,
                        userData->duktape,
                        objectRef
                );
            } else if (duk_is_function(ctx, -1)) {
                argVal = env->NewObject(
                        classCache.AtReneHollanderDuktapeValuesDukFunction,
                        methodIdCache.AtReneHollanderDuktapeValuesDukFunctionInit,
                        userData->duktape,
                        objectRef
                );
            } else {
                argVal = env->NewObject(
                        classCache.AtReneHollanderDuktapeValuesDukObject,
                        methodIdCache.AtReneHollanderDuktapeValuesDukObjectInit,
                        userData->duktape,
                        objectRef
                );
            }
        }

        if (argVal == NULL) {
            argVal = env->NewObject(
                    classCache.AtReneHollanderDuktapeValuesDukUndefined,
                    methodIdCache.AtReneHollanderDuktapeValuesDukUndefinedInit,
                    userData->duktape
            );
        }
        // fill from back to front to get correct order of arguments
        args[argc - 1 - i].l = argVal;
        duk_pop(ctx);
    }

    env->CallObjectMethodA(methodData->callerObject, methodData->methodID, args);

    resetJNIEnv(env);

    return 0;
}

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_values_DukJavaFunction__1createAndReference(JNIEnv *env, jclass cls, jlong contextPointer, jobject method, jint paramCount, jobject object) {
    duk_context *ctx = (void *) contextPointer;

    MethodData *methodData = (MethodData *) duk_push_fixed_buffer(ctx, sizeof(MethodData));
    int ref = duj_ref(ctx);

    methodData->callerObject = env->NewGlobalRef(object);
    methodData->methodID = env->FromReflectedMethod(method);

    duk_push_c_function(ctx, methodExecutor, paramCount);
    duk_push_int(ctx, ref);
    duk_put_prop_index(ctx, -2, 0);
    int function_ref = duj_ref(ctx);
    
    duk_dump_context_stdout(ctx);
    return function_ref;
}