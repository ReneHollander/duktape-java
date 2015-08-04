#include "duktape.h"
#include "duktape-java.h"

#include "method.h"
#include "cache.h"
#include "helper.h"
#include "objectwrapper.h"

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    jvm = vm;
    populateCache();
    return JNI_VERSION_1_6;
}

duk_context* getContextFromObject(JNIEnv *env, jobject obj) {
    return (duk_context *) env->GetLongField(obj, fieldIdCache.AtReneHollanderDuktapeDuktapeContextPtr);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_createContext(JNIEnv *env, jobject obj) {
    duk_context *ctx = duk_create_heap_default();
    env->SetLongField(obj, fieldIdCache.AtReneHollanderDuktapeDuktapeContextPtr, (jlong) ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_destroyContext(JNIEnv *env, jobject obj) {
    duk_context* ctx = getContextFromObject(env, obj);
    duk_destroy_heap(ctx);
}

int methodExecutor(duk_context *ctx) {
    JNIEnv* env = getJNIEnv();

    duk_push_heap_stash(ctx);
    duk_get_prop_index(ctx, -1, 0);
    duk_size_t size;
    MethodData* methodData = (MethodData*) duk_get_buffer(ctx, -1, &size);
    duk_pop(ctx);

    //int n = duk_get_top(ctx);  /* #args */

    //const jvalue args[2] = {5, 0x00};

    //jobjectArray params = env->NewObjectArray(1, classCache.object, NULL);
    //env->SetObjectArrayElement(params, 0, wrapInteger(5));
    /*

    DUK_TYPE_UNDEFINED
    DUK_TYPE_NULL
    DUK_TYPE_BOOLEAN
    DUK_TYPE_NUMBER
    DUK_TYPE_STRING
    DUK_TYPE_OBJECT
    */

    env->CallObjectMethod(methodData->callerObject, methodData->methodID, wrapInteger(env, 5), wrapLong(env, 7));

    return 0;
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_registerMethod(JNIEnv *env, jobject obj, jstring jName, jobject jObject, jobject jMethod, jint paramCount) {
    const char *name = env->GetStringUTFChars(jName, 0);
    duk_context* ctx = getContextFromObject(env, obj);

    duk_push_heap_stash(ctx);
    MethodData* methodData = (MethodData*) duk_push_fixed_buffer(ctx, sizeof(MethodData));
    duk_put_prop_index(ctx, -2, 0);
    duk_pop(ctx);

    methodData->callerObject = jObject;
    methodData->methodID = env->FromReflectedMethod(jMethod);

    duk_push_global_object(ctx);
    duk_push_c_function(ctx, methodExecutor, paramCount);
    duk_put_prop_string(ctx, -2, name);
    duk_pop(ctx);

    env->ReleaseStringUTFChars(jName, name);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_put(JNIEnv *env, jobject obj, jstring jName, jstring jValue) {
    duk_context* ctx = getContextFromObject(env, obj);
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
    duk_context* ctx = getContextFromObject(env, obj);
    const char *nativeScript = env->GetStringUTFChars(script, 0);

    duk_push_string(ctx, nativeScript);
    if (duk_peval(ctx) != 0) {
        printf("eval failed: %s\n", duk_safe_to_string(ctx, -1));
    }
    duk_pop(ctx);

    env->ReleaseStringUTFChars(script, nativeScript);
}
