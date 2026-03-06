#include "util/debug.h"
#include <glad/glad.h>
#include <stdio.h>

#define MAX_ERROR_LENGTH 30 // INVALID_FRAMEBUFFER_OPERATION

DEF_PRINT_GLM_VEC(2)
DEF_PRINT_GLM_VEC(3)
DEF_PRINT_GLM_VEC(4)
DEF_PRINT_MAT_SQ(4)

void debug_clear_errors()
{
    while (glGetError() != GL_NO_ERROR);
}

void debug_halt_on_error(const char *file, int line)
{
    int error = glGetError();
    if (error != GL_NO_ERROR)
        fprintf(stderr, "ERROR::GL::FILE%s::%d\n", file, line);
    ASSERT(error == GL_NO_ERROR);
}

