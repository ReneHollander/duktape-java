#include "duktape.h"
#include "duktape-java.h"

#include "method.h"
#include "cache.h"
#include "helper.h"
#include "objectwrapper.h"
#include "refs.h"
#include "memoryinfo.h"

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    jvm = vm;
    populateCache();
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_createContext(JNIEnv *env, jobject obj) {
    MemoryInfo *memoryInfo = (MemoryInfo *) malloc(sizeof(MemoryInfo));
    memoryInfo->currentHeapSize = 0;
    duk_context *ctx = duk_create_heap(counting_alloc_function, counting_realloc_function, counting_free_function, memoryInfo, NULL);
    duj_ref_setup(ctx);
    env->SetLongField(obj, fieldIdCache.AtReneHollanderDuktapeDuktapeContextPtr, (jlong) ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_destroyContext(JNIEnv *env, jobject obj) {
    duk_context *ctx = getContextFromObject(env, obj);
    duk_memory_functions functions;
    duk_get_memory_functions(ctx, &functions);
    duk_destroy_heap(ctx);
    free(functions.udata);
}

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

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_put(JNIEnv *env, jobject obj, jstring jName, jstring jValue) {
    duk_context *ctx = getContextFromObject(env, obj);
    duk_push_global_object(ctx);
    const char *name = env->GetStringUTFChars(jName, 0);
    const char *value = env->GetStringUTFChars(jValue, 0);
    duk_push_string(ctx, value);
    env->ReleaseStringUTFChars(jValue, value);
    duk_put_prop_string(ctx, -2, name);
    env->ReleaseStringUTFChars(jName, name);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_execute(JNIEnv *env, jobject obj, jstring script) {
    duk_context *ctx = getContextFromObject(env, obj);
    const char *nativeScript = env->GetStringUTFChars(script, 0);

    duk_push_string(ctx, nativeScript);
    if (duk_peval(ctx) != 0) {
        printf("eval failed: %s\n", duk_safe_to_string(ctx, -1));
    }
    duk_pop(ctx);
    env->ReleaseStringUTFChars(script, nativeScript);
}

JNIEXPORT jlong JNICALL Java_at_renehollander_duktape_Duktape_getHeapUsage(JNIEnv *env, jobject obj) {
    duk_context *ctx = getContextFromObject(env, obj);
    duk_memory_functions functions;
    duk_get_memory_functions(ctx, &functions);
    MemoryInfo *memoryInfo = (MemoryInfo *) functions.udata;
    return (jlong) memoryInfo->currentHeapSize;
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_gc(JNIEnv *env, jobject duktabe) {
    duk_context *ctx = getContextFromObject(env, duktabe);
    duk_gc(ctx, 0);
}