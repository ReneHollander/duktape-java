#include <stdlib.h>

#include "helper.h"

JavaVM *jvm = NULL;

JNIEnv* getJNIEnv() {
    JNIEnv* env;
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        printf("GetEnv failed.");
        exit(1);
    }
    return env;
}

