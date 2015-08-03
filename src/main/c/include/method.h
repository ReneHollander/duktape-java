#ifndef METHOD_H
#define METHOD_H

struct MethodData {
    jobject callerObject;
    jmethodID methodID;
};
typedef struct MethodData MethodData;

#endif