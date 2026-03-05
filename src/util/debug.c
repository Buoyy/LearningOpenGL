#include "util/debug.h"
#include <glad/glad.h>
#include <stdio.h>

#define MAX_ERROR_LENGTH 30 // INVALID_FRAMEBUFFER_OPERATION

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

