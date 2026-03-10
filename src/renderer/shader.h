#ifndef R_GFX_SHADER_H
#define R_GFX_SHADER_H

#include <cglm/cglm.h>

// ++---------------------------------------------++ 

#define DECL_SHADER_MAT_SET_SQ(N)\
void shader_set_mat##N(shader_t *shader, const char* name, mat##N matrix);\

#define DEF_SHADER_MAT_SET_SQ(N)\
void shader_set_mat##N(shader_t *shader, const char* name, mat##N matrix)\
{\
    GL(int location = glGetUniformLocation(shader->id, name));\
    ASSERTM(location != -1, "UNIFORM %s NOT FOUND", name);\
    GL(glUniformMatrix##N##fv(location, 1, GL_FALSE, (float*)matrix));\
}\

// ++---------------------------------------------++ 

#include "util/types.h"

typedef struct
{
    unsigned int id;
} shader_t;

boolean shader_create(shader_t *shader, const char *vert_path, const char *frag_path);
void shader_use(shader_t *shader);
void shader_destroy(shader_t *shader);

// Uniform 1 setters 
void shader_set_float(shader_t *shader, const char* name, float value);
void shader_set_int(shader_t *shader, const char* name, int value);

// Uniform n setters (n > 1) 
void shader_set_fvec2(shader_t *shader, const char* name, vec2 vec);
void shader_set_fvec3(shader_t *shader, const char* name, vec3 vec);
void shader_set_fvec4(shader_t *shader, const char* name, vec4 vec);
void shader_set_ivec2(shader_t *shader, const char* name, ivec2 vec);
void shader_set_ivec3(shader_t *shader, const char* name, ivec3 vec);
void shader_set_ivec4(shader_t *shader, const char* name, ivec4 vec);

DECL_SHADER_MAT_SET_SQ(4);

#endif
