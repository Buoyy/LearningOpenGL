#ifndef R_TEXTURE_H
#define R_TEXTURE_H

#include "util/types.h"

typedef struct 
{
    uint id;
    uint index;
} texture_2d;

void texture_2d_create(texture_2d *tex, uint index);
void texture_2d_activate(texture_2d *tex);
void texture_2d_bind(texture_2d *tex);
void texture_2d_unbind();
void texture_2d_load(const char *filepath, uint format);
void texture_2d_param(uint pname, uint param);
void texture_2d_destroy(texture_2d *tex);

#endif
