#include "duktape.h"
#include "duktape-java.h"

#include "method.h"
#include "cache.h"
#include "helper.h"

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    jvm = vm;

    JNIEnv* env = getJNIEnv();
    fieldIdCache.contextPtr = (*env)->GetFieldID(env, (*env)->FindClass(env, "at/renehollander/duktape/Duktape"), "contextPtr", "J");

    return JNI_VERSION_1_6;
}

duk_context* getContextFromObject(JNIEnv *env, jobject obj) {
    return (duk_context *) (*env)->GetLongField(env, obj, fieldIdCache.contextPtr);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_createContext(JNIEnv *env, jobject obj) {
    duk_context *ctx = duk_create_heap_default();
    (*env)->SetLongField(env, obj, fieldIdCache.contextPtr, (jlong) ctx);
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

    (*env)->CallObjectMethod(env, methodData->callerObject, methodData->methodID);

    return 0;
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_registerMethod(JNIEnv *env, jobject obj, jstring jName, jobject jObject, jobject jMethod) {
    const char *name = (*env)->GetStringUTFChars(env, jName, 0);
    duk_context* ctx = getContextFromObject(env, obj);

    duk_push_heap_stash(ctx);
    MethodData* methodData = (MethodData*) duk_push_fixed_buffer(ctx, sizeof(MethodData));
    duk_put_prop_index(ctx, -2, 0);
    duk_pop(ctx);

    methodData->callerObject = (*env)->NewGlobalRef(env, jObject);
    methodData->methodID = (*env)->FromReflectedMethod(env, jMethod);

    duk_push_global_object(ctx);
    duk_push_c_function(ctx, methodExecutor, DUK_VARARGS);
    duk_put_prop_string(ctx, -2, name);
    duk_pop(ctx);

    (*env)->ReleaseStringUTFChars(env, jName, name);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_put(JNIEnv * env, jobject obj, jstring jName, jstring jValue) {
    duk_context* ctx = getContextFromObject(env, obj);
    duk_push_global_object(ctx);
    const char *name = (*env)->GetStringUTFChars(env, jName, 0);
    const char *value = (*env)->GetStringUTFChars(env, jValue, 0);
    duk_push_string(ctx, value);
    (*env)->ReleaseStringUTFChars(env, jValue, value);
    duk_put_prop_string(ctx, -2, name);
    (*env)->ReleaseStringUTFChars(env, jName, name);
    duk_pop(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_execute(JNIEnv *env, jobject obj, jstring script) {
    duk_context* ctx = getContextFromObject(env, obj);
    const char *nativeScript = (*env)->GetStringUTFChars(env, script, 0);

    duk_push_string(ctx, nativeScript);
    if (duk_peval(ctx) != 0) {
        printf("eval failed: %s\n", duk_safe_to_string(ctx, -1));
    }
    duk_pop(ctx);

    (*env)->ReleaseStringUTFChars(env, script, nativeScript);
}
