/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class at_renehollander_duktape_Duktape */

#ifndef _Included_at_renehollander_duktape_Duktape
#define _Included_at_renehollander_duktape_Duktape
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     at_renehollander_duktape_Duktape
 * Method:    createContext
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_createContext
        (JNIEnv *, jobject);

/*
 * Class:     at_renehollander_duktape_Duktape
 * Method:    destroyContext
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_destroyContext
        (JNIEnv *, jobject);

/*
 * Class:     at_renehollander_duktape_Duktape
 * Method:    put
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_put
        (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     at_renehollander_duktape_Duktape
 * Method:    registerMethod
 * Signature: (Ljava/lang/String;Ljava/lang/Object;Ljava/lang/reflect/Method;I)V
 */
JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_registerMethod
        (JNIEnv *, jobject, jstring, jobject, jobject, jint);

/*
 * Class:     at_renehollander_duktape_Duktape
 * Method:    execute
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_execute
        (JNIEnv *, jobject, jstring);

/*
 * Class:     at_renehollander_duktape_Duktape
 * Method:    getHeapUsage
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_at_renehollander_duktape_Duktape_getHeapUsage
        (JNIEnv *, jobject);

/*
 * Class:     at_renehollander_duktape_Duktape
 * Method:    gc
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_at_renehollander_duktape_Duktape_gc
        (JNIEnv *, jobject);

/*
 * Class:     at_renehollander_duktape_Duktape
 * Method:    getRefCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_at_renehollander_duktape_Duktape_getRefCount
        (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
