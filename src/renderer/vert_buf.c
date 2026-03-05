#include "util/debug.h"
#include "util/vector.h"
#include "renderer/vert_buf.h"
#include <glad/glad.h>

VECTOR_DEFINE(vert, vertvec);

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
