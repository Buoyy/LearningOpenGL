#ifndef R_VERTEX_BUFFER_H
#define R_VERTEX_BUFFER_H

#include "util/vector.h"
#include "util/types.h"
#include <cglm/cglm.h>

typedef struct 
{
    vec2 pos;
    solid_color color;
    vec2 uv;
} vert;

// A vector (dynamic array) of vertices.
VECTOR_DECLARE(vert, vertvec);

typedef struct 
{
    unsigned int id;
    vertvec verts;
} vert_buf;

void vb_create(vert_buf *vb);
void vb_push_verts(vert_buf *vb, int usage);
void vb_bind(vert_buf *vb);
void vb_unbind();
void vb_destroy(vert_buf *vb);

#endif
