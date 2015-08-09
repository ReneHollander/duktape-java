/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class at_renehollander_duktape_values_DukObject */

#ifndef _Included_at_renehollander_duktape_values_DukObject
#define _Included_at_renehollander_duktape_values_DukObject
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     at_renehollander_duktape_values_DukObject
 * Method:    size
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_at_renehollander_duktape_values_DukObject_size
        (JNIEnv *, jobject);

/*
 * Class:     at_renehollander_duktape_values_DukObject
 * Method:    clear
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject_clear
        (JNIEnv *, jobject);

/*
 * Class:     at_renehollander_duktape_values_DukObject
 * Method:    toJSON
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_at_renehollander_duktape_values_DukObject_toJSON
        (JNIEnv *, jobject);

/*
 * Class:     at_renehollander_duktape_values_DukObject
 * Method:    _containsKey
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_at_renehollander_duktape_values_DukObject__1containsKey
        (JNIEnv *, jobject, jstring);

/*
 * Class:     at_renehollander_duktape_values_DukObject
 * Method:    _get
 * Signature: (Ljava/lang/String;)Lat/renehollander/duktape/values/DukValue;
 */
JNIEXPORT jobject JNICALL Java_at_renehollander_duktape_values_DukObject__1get
        (JNIEnv *, jobject, jstring);

/*
 * Class:     at_renehollander_duktape_values_DukObject
 * Method:    _remove
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1remove
        (JNIEnv *, jobject, jstring);

/*
 * Class:     at_renehollander_duktape_values_DukObject
 * Method:    _putDouble
 * Signature: (Ljava/lang/String;D)V
 */
JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putDouble
        (JNIEnv *, jobject, jstring, jdouble);

/*
 * Class:     at_renehollander_duktape_values_DukObject
 * Method:    _putBoolean
 * Signature: (Ljava/lang/String;Z)V
 */
JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putBoolean
        (JNIEnv *, jobject, jstring, jboolean);

/*
 * Class:     at_renehollander_duktape_values_DukObject
 * Method:    _putString
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putString
        (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     at_renehollander_duktape_values_DukObject
 * Method:    _putUndefined
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putUndefined
        (JNIEnv *, jobject, jstring);

/*
 * Class:     at_renehollander_duktape_values_DukObject
 * Method:    _putNull
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putNull
        (JNIEnv *, jobject, jstring);

/*
 * Class:     at_renehollander_duktape_values_DukObject
 * Method:    _putReference
 * Signature: (Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_at_renehollander_duktape_values_DukObject__1putReference
        (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     at_renehollander_duktape_values_DukObject
 * Method:    createEmptyObject
 * Signature: (Lat/renehollander/duktape/Duktape;)I
 */
JNIEXPORT jint JNICALL Java_at_renehollander_duktape_values_DukObject_createEmptyObject
        (JNIEnv *, jclass, jobject);

#ifdef __cplusplus
}
#endif
#endif
