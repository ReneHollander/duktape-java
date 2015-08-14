#include "duk-java-function.h"
#include "duktape.h"
#include "refs.h"
#include "helper.h"

struct MethodData {
    jobject callerObject;
    jmethodID methodID;
};
typedef struct MethodData MethodData;

int methodExecutor(duk_context *ctx) {
    JNIEnv *env = setupJNIEnv();

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
        // fill from back to front to get correct order of arguments
        args[argc - 1 - i].l = duj_value_to_java_object(env, ctx);
    }

    jobject retval = env->CallObjectMethodA(methodData->callerObject, methodData->methodID, args);
    duj_java_object_to_value(env, ctx, retval);
    resetJNIEnv(env);
    return 1;
}

int methodFinalizer(duk_context *ctx) {
    JNIEnv *env = setupJNIEnv();

    duk_get_prop_index(ctx, -1, 0);
    int ref = duk_get_int(ctx, -1);
    duk_pop(ctx);
    duk_pop(ctx);

    duk_size_t size;
    duj_push_ref(ctx, ref);
    MethodData *methodData = (MethodData *) duk_get_buffer(ctx, -1, &size);
    duk_pop(ctx);

    env->DeleteGlobalRef(methodData->callerObject);
    duj_unref(ctx, ref);

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
    duk_push_c_function(ctx, methodFinalizer, 1);
    duk_set_finalizer(ctx, -2);
    int function_ref = duj_ref(ctx);

    return function_ref;
}