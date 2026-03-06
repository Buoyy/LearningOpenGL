#ifndef R_VERTEX_ARRAY_H
#define R_VERTEX_ARRAY_H

#include "util/types.h"
#include <stddef.h>

typedef struct 
{ 
    unsigned int id; 
} vert_array;

void va_create(vert_array *va);
void va_bind(vert_array *va);
void va_add_attrib(uint index, uint count, uint type, boolean normalize, size_t stride, const void *offset);
void va_unbind();
void va_destroy(vert_array *va);

#endif
