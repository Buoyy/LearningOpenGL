#include "renderer/vert_array.h"
#include "util/debug.h"
#include <glad/glad.h>

void va_create(vert_array *va)
{
    GL(glGenVertexArrays(1, &va->id));
    GL(glBindVertexArray(va->id));
}

void va_bind(vert_array *va)
{
    GL(glBindVertexArray(va->id));
}

void va_add_attrib(uint index, uint count, uint type, boolean normalize, size_t stride, const void *offset)
{
    GL(glVertexAttribPointer(index, count, type, normalize, stride, offset));
    GL(glEnableVertexAttribArray(index));
}

void va_unbind()
{
    GL(glBindVertexArray(0));
}

void va_destroy(vert_array *va)
{
    GL(glDeleteVertexArrays(1, &va->id));
}
