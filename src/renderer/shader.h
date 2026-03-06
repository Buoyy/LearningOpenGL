#ifndef R_GFX_SHADER_H
#define R_GFX_SHADER_H

#include <cglm/cglm.h>

#define DECL_SHADER_UNI_SET(TYPE, NAME, SUFFIX)\
void shader_set_##NAME(shader_t *shader, const char *name, TYPE value);\
void shader_set_##NAME##2(shader_t *shader, const char *name, TYPE value1, TYPE value2);\
void shader_set_##NAME##3(shader_t *shader, const char *name, TYPE value1, TYPE value2, TYPE value3);\
void shader_set_##NAME##4(shader_t *shader, const char *name, TYPE value1, TYPE value2, TYPE value3, TYPE value4)\

#define DEF_SHADER_UNI_SET(TYPE, NAME, SUFFIX)\
void shader_set_##NAME(shader_t *shader, const char *name, TYPE value)\
{\
    GL(int location = glGetUniformLocation(shader->id, name));\
    ASSERT(location != -1);\
    GL(glUniform1##SUFFIX(location, value));\
}\
\
void shader_set_##NAME##2(shader_t *shader, const char *name, TYPE value1, TYPE value2)\
{\
    GL(int location = glGetUniformLocation(shader->id, name));\
    ASSERT(location != -1);\
    GL(glUniform2##SUFFIX(location, value1, value2));\
}\
\
void shader_set_##NAME##3(shader_t *shader, const char *name, TYPE value1, TYPE value2, TYPE value3)\
{\
    GL(int location = glGetUniformLocation(shader->id, name));\
    ASSERT(location != -1);\
    GL(glUniform3##SUFFIX(location, value1, value2, value3));\
}\
\
void shader_set_##NAME##4(shader_t *shader, const char *name, TYPE value1, TYPE value2, TYPE value3, TYPE value4)\
{\
    GL(int location = glGetUniformLocation(shader->id, name));\
    ASSERT(location != -1);\
    GL(glUniform4##SUFFIX(location, value1, value2, value3, value4));\
}\

// ++---------------------------------------------++ 

#define DECL_SHADER_MAT_SET_SQ(N)\
void shader_set_mat##N(shader_t *shader, const char* name, mat##N matrix);\

#define DEF_SHADER_MAT_SET_SQ(N)\
void shader_set_mat##N(shader_t *shader, const char* name, mat##N matrix)\
{\
    GL(int location = glGetUniformLocation(shader->id, name));\
    ASSERT(location != 1);\
    GL(glUniformMatrix##N##fv(location, 1, GL_FALSE, (float*)matrix));\
}\


#include "util/types.h"

typedef struct
{
    unsigned int id;
} shader_t;

boolean shader_create(shader_t *shader, const char *vert_path, const char *frag_path);
void shader_use(shader_t *shader);
void shader_destroy(shader_t *shader);

DECL_SHADER_UNI_SET(int, int,i);
DECL_SHADER_UNI_SET(float, float, f);
DECL_SHADER_UNI_SET(boolean, boolean, i);

DECL_SHADER_MAT_SET_SQ(4);

#endif
