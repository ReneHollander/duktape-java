#include "duktape.h"
#include "duktape-java.h"

#include "cache.h"
#include "helper.h"
#include "refs.h"

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    jvm = vm;
    populateCache();
    return JNI_VERSION_1_6;
}

void duj_fatal_handler(duk_context *ctx, duk_errcode_t code, const char *msg) {
    JNIEnv *env = getJNIEnv();
    DuktapeUserData *userData = getDuktapeUserData(ctx);
    env->CallObjectMethod(userData->duktape, methodIdCache.AtReneHollanderDuktapeDuktapeFatalErrorHandler, code, env->NewStringUTF(msg));
}

JNIEXPORT jlong JNICALL Java_at_renehollander_duktape_Duktape__1createContext(JNIEnv *env, jclass cls, jobject duktape) {
    DuktapeUserData *userData = (DuktapeUserData *) malloc(sizeof(MemoryInfo));
    userData->memoryInfo.currentHeapSize = 0;
    duk_context *ctx = duk_create_heap(counting_alloc_function, counting_realloc_function, counting_free_function, userData, duj_fatal_handler);
    duj_ref_setup(ctx);

    userData->duktape = env->NewGlobalRef(duktape);

    return (jlong) ctx;
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape__1destroyContext(JNIEnv *env, jclass cls, jlong contextPointer) {
    duk_context *ctx = (void *) contextPointer;
    DuktapeUserData *duktapeUserData = getDuktapeUserData(ctx);

    duk_destroy_heap(ctx);

    env->DeleteGlobalRef(duktapeUserData->duktape);

    free(duktapeUserData);
}

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_Duktape__1getRefCount(JNIEnv *env, jclass cls, jlong contextPointer) {
    duk_context *ctx = (void *) contextPointer;
    return duj_get_ref_count(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape__1gc(JNIEnv *env, jclass cls, jlong contextPointer) {
    duk_context *ctx = (void *) contextPointer;
    duk_gc(ctx, 0);
}

JNIEXPORT jlong JNICALL Java_at_renehollander_duktape_Duktape__1getHeapUsage(JNIEnv *env, jclass cls, jlong contextPointer) {
    duk_context *ctx = (void *) contextPointer;
    DuktapeUserData *userData = getDuktapeUserData(ctx);
    return (jlong) userData->memoryInfo.currentHeapSize;
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape__1execute(JNIEnv *env, jclass cls, jlong contextPointer, jstring jScript) {
    duk_context *ctx = (void *) contextPointer;
    const char *script = env->GetStringUTFChars(jScript, 0);

    duk_push_string(ctx, script);
    if (duk_peval(ctx) != 0) {
        printf("eval failed: %s\n", duk_safe_to_string(ctx, -1));
    }
    duk_pop(ctx);
    env->ReleaseStringUTFChars(jScript, script);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape__1registerMethod(JNIEnv *env, jclass cls, jlong contextPointer, jstring, jobject, jobject, jint) {
    //duk_context *ctx = (void *) contextPointer;
}

/*
int methodExecutor(duk_context *ctx) {
    JNIEnv *env = getJNIEnv();

    duk_push_current_function(ctx);
    duk_get_prop_index(ctx, -1, 0);
    int ref = duk_get_int(ctx, -1);

    duk_size_t size;
    duj_push_ref(ctx, ref);
    MethodData *methodData = (MethodData *) duk_get_buffer(ctx, -1, &size);

    // just testing if I can call something from c++
    env->CallObjectMethod(methodData->callerObject, methodData->methodID, wrapInteger(env, 5), wrapLong(env, 7));

    return 0;
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_registerMethod(JNIEnv *env, jobject obj, jstring jName, jobject jObject, jobject jMethod, jint paramCount) {
    const char *name = env->GetStringUTFChars(jName, 0);
    duk_context *ctx = getContextFromObject(env, obj);

    MethodData *methodData = (MethodData *) duk_push_fixed_buffer(ctx, sizeof(MethodData));
    int ref = duj_ref(ctx);

    methodData->callerObject = jObject;
    methodData->methodID = env->FromReflectedMethod(jMethod);

    duk_push_global_object(ctx);
    duk_push_c_function(ctx, methodExecutor, paramCount);
    duk_push_int(ctx, ref);
    duk_put_prop_index(ctx, -2, 0);
    duk_put_prop_string(ctx, -2, name);
    duk_pop(ctx);

    env->ReleaseStringUTFChars(jName, name);
}
 */