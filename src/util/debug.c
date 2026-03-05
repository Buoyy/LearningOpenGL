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
    /*
    char message[MAX_ERROR_LENGTH];
    switch (error)
    {
        case GL_INVALID_ENUM:
            strcpy(message, "INVALID_ENUM"); break;
        case GL_INVALID_VALUE:
            strcpy(message, "INVALID_VALUE"); break;
        case GL_INVALID_OPERATION:
            strcpy(message, "INVALID_OPERATION"); break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            strcpy(message, "INVALID_FRAMEBUFFER_OPERATION"); break;
        case GL_OUT_OF_MEMORY:
            strcpy(message, "OUT_OF_MEMORY"); break;
    }
    */
    if (error != GL_NO_ERROR)
        fprintf(stderr, "ERROR::GL::FILE%s::%d\n", file, line);
    ASSERT(error == GL_NO_ERROR);
}
