#include "util/debug.h"
#include "renderer/index_buf.h"
#include <glad/glad.h>

VECTOR_DEFINE(unsigned int, uivec);
void uivec_push_list(uivec *vec, int count, ...)
{
    va_list uints;
    va_start(uints, count);
    for (int i = 0; i < count; ++i)
        uivec_push(vec, va_arg(uints, unsigned int));
    va_end(uints);
}
void ib_create(index_buf *ib)
{
    GL(glGenBuffers(1, &ib->id));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->id));
    uivec_init(&ib->indices);
}

void ib_bind(index_buf *ib)
{
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->id));
}

void ib_push_indices(index_buf *ib, unsigned int usage)
{
    GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*ib->indices.length, ib->indices.data, usage));
}

void ib_unbind()
{
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void ib_destroy(index_buf *ib)
{
    GL(glDeleteBuffers(1, &ib->id));
    uivec_destroy(&ib->indices);
}
