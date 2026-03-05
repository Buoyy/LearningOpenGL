#ifndef R_INDEX_BUFFER_H
#define R_INDEX_BUFFER_H

#include "util/vector.h"
#include "stdarg.h"

VECTOR_DECLARE(unsigned int, uivec)
void uivec_push_list(uivec *vec, int count, ...);

typedef struct 
{
    unsigned int id;
    uivec indices;
} index_buf;

void ib_create(index_buf *ib);
void ib_bind(index_buf *ib);
void ib_push_indices(index_buf *ib, unsigned int usage);
void ib_unbind();
void ib_destroy(index_buf *ib);

#endif
