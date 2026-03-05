#ifndef UTIL_VECTOR_H
#define UTIL_VECTOR_H

#include "util/debug.h"
#include <stdlib.h>
#include <string.h>

#define VECTOR_INIT_CAP 4

// Declares a vector struct of type TYPE and name NAME.
#define VECTOR_DECLARE(TYPE, NAME)\
typedef struct\
{\
    TYPE *data;\
    int length, capacity;\
} NAME;\
\
void NAME##_init(NAME *vec);\
void NAME##_push(NAME *vec, TYPE value);\
TYPE NAME##_at(NAME *vec, int index);\
TYPE NAME##_pop(NAME *vec);\
void NAME##_erase(NAME *vec, int index);\
void NAME##_set(NAME *vec, int index, TYPE value);\
void NAME##_insert(NAME *vec, int index, TYPE value);\
void NAME##_clear(NAME *vec);\

// Defintions. Yay.
#define VECTOR_DEFINE(TYPE, NAME)\
\
void NAME##_init(NAME *vec)\
{\
    vec->capacity = VECTOR_INIT_CAP;\
    vec->length = 0;\
    vec->data = malloc(sizeof(TYPE)*vec->capacity);\
    ASSERT(vec->data);\
}\
\
void NAME##_push(NAME *vec, TYPE value)\
{\
    ASSERT(vec->data);\
    if (vec->length+1 > vec->capacity)\
    {\
        vec->capacity *= 2;\
        TYPE *temp = realloc(vec->data, sizeof(TYPE)*vec->capacity);\
        ASSERT(temp);\
        vec->data = temp;\
    }\
    vec->data[vec->length++] = value;\
}\
\
TYPE NAME##_at(NAME *vec, int index)\
{\
    ASSERT(vec->data);\
    ASSERT(index > -1 && index < vec->length);\
    return vec->data[index];\
}\
\
TYPE NAME##_pop(NAME *vec)\
{\
    ASSERT(vec->data);\
    TYPE value = vec->data[vec->length - 1];\
    NAME##_erase(vec, vec->length - 1);\
    return value;\
}\
void NAME##_erase(NAME *vec, int index)\
{\
    ASSERT(vec->data);\
    ASSERT(index > -1 && index < vec->length);\
    memmove(&vec->data[index], &vec->data[index+1], sizeof(TYPE)*(vec->length-index-1));\
    --vec->length;\
}\
void NAME##_set(NAME *vec, int index, TYPE value)\
{\
    ASSERT(vec->data);\
    ASSERT(index > -1 && index < vec->length);\
    vec->data[index] = value;\
}\
void NAME##_insert(NAME *vec, int index, TYPE value)\
{\
    ASSERT(vec->data);\
    ASSERT(index > -1 && index < vec->length);\
    if (vec->length + 1 > vec->capacity)\
    {\
        vec->capacity *= 2;\
        TYPE *temp = realloc(vec->data, sizeof(TYPE)*vec->capacity);\
        ASSERT(temp);\
        vec->data = temp;\
    }\
    memmove(&vec->data[index+1], &vec->data[index], sizeof(TYPE)*(vec->length-index));\
    vec->data[index] = value;\
    ++vec->length;\
}\
void NAME##_clear(NAME *vec)\
{\
    ASSERT(vec->data);\
    vec->length = 0;\
}\
void NAME##_destroy(NAME *vec)\
{\
    ASSERT(vec->data != NULL);\
    free(vec->data);\
    vec->data = NULL;\
    vec->length = 0;\
    vec->capacity = 0;\
}\

#endif
