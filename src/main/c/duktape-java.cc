#include <iosfwd>
#include <sstream>
#include <method.h>
#include <objectwrapper.h>
#include "duktape-java.h"
#include "refs.h"

using namespace std;

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    jvm = vm;
    populateCache();
    return JNI_VERSION_1_6;
}

JNIEXPORT jstring JNICALL Java_at_renehollander_duktape_Duktape__1getVersion(JNIEnv *env, jclass cls) {
    stringstream version;
    version << DUK_VERSION / 10000 << "." << DUK_VERSION % 10000 / 100 << "." << DUK_VERSION % 10000 % 100;
    return env->NewStringUTF(version.str().c_str());
}

void duj_fatal_handler(duk_context *ctx, duk_errcode_t code, const char *msg) {
    JNIEnv *env = setupJNIEnv();
    DuktapeUserData *userData = getDuktapeUserData(ctx);
    env->CallObjectMethod(userData->duktape, methodIdCache.AtReneHollanderDuktapeDuktapeFatalErrorHandler, code, env->NewStringUTF(msg));
    resetJNIEnv(env);
}

JNIEXPORT jlong JNICALL Java_at_renehollander_duktape_Duktape__1createContext(JNIEnv *env, jclass cls, jobject duktape) {
    DuktapeUserData *userData = (DuktapeUserData *) malloc(sizeof(MemoryInfo));
    userData->memoryInfo.currentHeapSize = 0;
    duk_context *ctx = duk_create_heap(counting_alloc_function, counting_realloc_function, counting_free_function, userData, duj_fatal_handler);
    duj_ref_setup(ctx);

    // Store Array.splice on heap stash to protect it from modification with prototyping
    duk_push_array(ctx);
    duk_get_prop_string(ctx, -1, "splice");
    duj_ref(ctx, "Array.splice");
    duk_pop(ctx);

    userData->duktape = env->NewGlobalRef(duktape);
    userData->unrefData.mark_for_unref_indexed = new std::vector<int>();
    userData->unrefData.mark_for_unref_named = new std::vector<std::string>();

    return (jlong) ctx;
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape__1destroyContext(JNIEnv *env, jclass cls, jlong contextPointer) {
    duk_context *ctx = (void *) contextPointer;
    DuktapeUserData *userData = getDuktapeUserData(ctx);

    duk_destroy_heap(ctx);

    env->DeleteGlobalRef(userData->duktape);
    delete userData->unrefData.mark_for_unref_indexed;
    delete userData->unrefData.mark_for_unref_named;

    free(userData);
}

JNIEXPORT jint JNICALL Java_at_renehollander_duktape_Duktape__1getRefCount(JNIEnv *env, jclass cls, jlong contextPointer) {
    duk_context *ctx = (void *) contextPointer;
    return duj_get_ref_count(ctx);
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape__1gc(JNIEnv *env, jclass cls, jlong contextPointer) {
    duk_context *ctx = (void *) contextPointer;
    duj_check_marked_for_unref(ctx);
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

int methodExecutor(duk_context *ctx) {
    JNIEnv *env = setupJNIEnv();

    duk_push_current_function(ctx);
    duk_get_prop_index(ctx, -1, 0);
    int ref = duk_get_int(ctx, -1);

    duk_size_t size;
    duj_push_ref(ctx, ref);
    MethodData *methodData = (MethodData *) duk_get_buffer(ctx, -1, &size);

    // just testing if I can call something from c++

    /*
    jvalue args[2];
    args[0].i = (jint) 5;
    args[1].j = (jlong) 7;
    */

    jvalue args[2];
    args[0].l = wrapInteger(env, 5);
    args[1].l = wrapLong(env, 7);

    env->CallObjectMethodA(methodData->callerObject, methodData->methodID, args);

    resetJNIEnv(env);

    return 0;
}

JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape__1registerMethod(JNIEnv *env, jclass cls, jlong contextPointer, jstring jName, jobject callerObject, jobject method, jint paramCount) {
    duk_context *ctx = (void *) contextPointer;
    const char *name = env->GetStringUTFChars(jName, 0);
    MethodData *methodData = (MethodData *) duk_push_fixed_buffer(ctx, sizeof(MethodData));
    int ref = duj_ref(ctx);

    methodData->callerObject = env->NewGlobalRef(callerObject);
    methodData->methodID = env->FromReflectedMethod(method);

    duk_push_global_object(ctx);
    duk_push_c_function(ctx, methodExecutor, paramCount);
    duk_push_int(ctx, ref);
    duk_put_prop_index(ctx, -2, 0);
    duk_put_prop_string(ctx, -2, name);
    duk_pop(ctx);

    env->ReleaseStringUTFChars(jName, name);
}
