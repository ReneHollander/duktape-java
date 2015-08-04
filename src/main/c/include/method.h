#pragma once

struct MethodData {
    jobject callerObject;
    jmethodID methodID;
};
typedef struct MethodData MethodData;