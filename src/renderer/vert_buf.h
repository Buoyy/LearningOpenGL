#ifndef R_VERTEX_BUFFER_H
#define R_VERTEX_BUFFER_H

#include "util/vector.h"
#include <cglm/cglm.h>
#include <stdarg.h>

typedef struct 
{
    vec3 pos;
} vert;

// A vector (dynamic array) of vertices.
VECTOR_DECLARE(vert, vertvec);
void vertvec_push_list(vertvec *vec, int count, ...);

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
