#include "util/debug.h"
#include "util/vector.h"
#include "renderer/vert_buf.h"
#include <glad/glad.h>

VECTOR_DEFINE(vert, vertvec);
void vertvec_push_list(vertvec *vec, int count, ...)
{
    va_list verts;
    va_start(verts, count);
    for (int i = 0; i < count; ++i)
        vertvec_push(vec, va_arg(verts, vert));
    va_end(verts);
}

void vb_create(vert_buf *vb) 
{
    GL(glGenBuffers(1, &vb->id));
    vb_bind(vb);
    vertvec_init(&vb->verts);
}

void vb_push_verts(vert_buf *vb, int usage)
{
    GL(glBufferData(GL_ARRAY_BUFFER, sizeof(vert)*vb->verts.length, vb->verts.data, usage));
}

void vb_bind(vert_buf *vb)
{
    GL(glBindBuffer(GL_ARRAY_BUFFER, vb->id));
}

void vb_unbind()
{
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void vb_destroy(vert_buf *vb)
{
    GL(glDeleteBuffers(1, &vb->id));
    vertvec_destroy(&vb->verts);
}
