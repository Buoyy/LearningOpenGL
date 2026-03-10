#include "renderer/texture.h"

#include "util/types.h"
#include "util/debug.h"
#include <glad/glad.h>
#include "stb_image.h"

#include <stdarg.h>

void texture_2d_create(texture_2d *tex, uint index)
{
    GL(glGenTextures(1, &tex->id));
    tex->index = GL_TEXTURE0 + index;
    texture_2d_activate(tex);
}

void texture_2d_activate(texture_2d *tex)
{
    GL(glActiveTexture(tex->index));
    texture_2d_bind(tex);
}

void texture_2d_bind(texture_2d *tex)
{
    GL(glBindTexture(GL_TEXTURE_2D, tex->id));
}

void texture_2d_unbind()
{
    GL(glBindTexture(GL_TEXTURE_2D, 0));
}

void texture_2d_param(uint pname, uint param)
{
    GL(glTexParameteri(GL_TEXTURE_2D, pname, param));
}

void texture_2d_params(texture_2d *tex, ...)
{
    va_list params;
    va_start(params, tex);
    texture_2d_param(GL_TEXTURE_WRAP_S, va_arg(params, uint));
    texture_2d_param(GL_TEXTURE_WRAP_T, va_arg(params, uint));
    texture_2d_param(GL_TEXTURE_MIN_FILTER, va_arg(params, uint));
    texture_2d_param(GL_TEXTURE_MAG_FILTER, va_arg(params, uint));
    va_end(params);
}
void texture_2d_load(const char *filepath, uint format)
{
    int x, y, channels;
    byte *pixels = stbi_load(filepath, &x, &y, &channels, 0);
    ASSERT(pixels != NULL);
    GL(glTexImage2D(GL_TEXTURE_2D, 0, format, x, y, 0, format, GL_UNSIGNED_BYTE, pixels));
    GL(glGenerateMipmap(GL_TEXTURE_2D));
    stbi_image_free(pixels);
}

void texture_2d_create_default(texture_2d *tex, uint index, const char *filepath, uint format)
{
    texture_2d_create(tex, index);
    texture_2d_params(tex, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
    texture_2d_load(filepath, format);
}

void texture_2d_destroy(texture_2d *tex)
{
    GL(glDeleteTextures(1, &tex->id));
}
