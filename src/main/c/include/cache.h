#ifndef CACHE_H
#define CACHE_H

struct ClassCache {
};
typedef struct ClassCache ClassCache;

struct MethodIDCache {
};
typedef struct MethodIDCache MethodIDCache;

struct FieldIDCache {
    jfieldID contextPtr;
} fieldIdCache;
typedef struct FieldIDCache FieldIDCache;

#endif