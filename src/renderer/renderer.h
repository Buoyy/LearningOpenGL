#ifndef E_GFX_RENDERER_H
#define E_GFX_RENDERER_H

#include <glad/glad.h>
#include "engine/window.h"
#include "renderer/index_buf.h"
#include "util/types.h"
#include <stdbool.h>

bool renderer_init(window_t *window);
void renderer_clear(bytevec3 color);
void renderer_draw_triangles(int first, int count);
void renderer_draw_elements(int mode, index_buf *ib);

#endif
