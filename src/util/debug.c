#include "util/debug.h"
#include <glad/glad.h>

#include <stdarg.h>
#include <stdio.h>

#define MAX_ERROR_LENGTH 30 // INVALID_FRAMEBUFFER_OPERATIO

void assertm_impl(boolean condition, const char* file, int line, const char *fmt, ...)
{
    if (condition) return;

    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "[%s:%d] ASSERT FAILED: ", file, line);
    vprintf(fmt, args);
    printf("\n");

    va_end(args);

    BREAKPOINT();
}

void assert_impl(boolean condition, const char *file, int line)
{
    if (condition) return;

    fprintf(stderr, "[%s:%d] ASSERT FAILED\n", file, line);
    BREAKPOINT();
}

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

