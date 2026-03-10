#include "renderer/shader.h"
#include "util/debug.h"
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFO_LOG_LENGTH 512
#define SHADER_TYPENAME_LENGTH 4

DEF_SHADER_UNI_SET(int, int, i);
DEF_SHADER_UNI_SET(float, float, f);
DEF_SHADER_UNI_SET(boolean, boolean, i);

DEF_SHADER_MAT_SET_SQ(4);

static boolean shader_part_validate(unsigned int id)
{
    int success;
    GL(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
    if (!success)
    {
        int type;
        char info_log[INFO_LOG_LENGTH];
        GL(glGetShaderiv(id, GL_SHADER_TYPE, &type));
        char typename[SHADER_TYPENAME_LENGTH+1];
        switch (type)
        {
            case GL_VERTEX_SHADER: 
                strncpy(typename, "VERT", 4); break;
            case GL_FRAGMENT_SHADER:
                strncpy(typename, "FRAG", 4); break;
            default: 
                strncpy(typename, "NULL", 4); break;
        }
        GL(glGetShaderInfoLog(id, INFO_LOG_LENGTH, NULL, info_log));
        fprintf(stderr, "ERROR::SHADER::%s::COMPILE_FAIL:%s\n", typename, info_log);
        return false;
    }
    return true;
}

static boolean shader_validate(shader_t *shader)
{
    int success;
    GL(glGetProgramiv(shader->id, GL_LINK_STATUS, &success));
    if (!success)
    {
        char info_log[INFO_LOG_LENGTH];
        GL(glGetProgramInfoLog(shader->id, INFO_LOG_LENGTH, NULL, info_log));
        fprintf(stderr, "ERROR::SHADER::PROGRAM::LINK_FAIL:%s\n", info_log);
        return false;
    }
    return true;
}
static char *read_entire_file(const char *path)
{
    FILE *file = fopen(path, "rb");
    if (!file)
    {
        perror("ERROR::FILE::FOPEN_FAIL");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);
    char *buf = malloc(length + 1);
    if (!buf)
    {
        perror("ERROR::STDLIB::MALLOC_FAIL");
        fclose(file);
        return NULL;
    }
    size_t bytes_read = fread(buf, sizeof(char), length,file);
    if (bytes_read != (size_t)length)
    {
        perror("ERROR::FILE::READ_FAIL");
        fclose(file);
        free(buf);
        return NULL;
    }
    buf[length] = 0;
    fclose(file);
    return buf;
}

boolean shader_create(shader_t *shader, const char *vert_path, const char *frag_path)
{
    GL(unsigned int vert = glCreateShader(GL_VERTEX_SHADER));
    char *vert_src = read_entire_file(vert_path);
    if (!vert_src) 
        return false;
    GL(glShaderSource(vert, 1, (const char**)&vert_src, NULL));
    GL(glCompileShader(vert));
    if (!shader_part_validate(vert)) 
        return false;
    free(vert_src);

    GL(unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER));
    char *frag_src = read_entire_file(frag_path);
    if (!frag_src)
        return false;
    GL(glShaderSource(frag, 1, (const char**)&frag_src, NULL));
    GL(glCompileShader(frag));
    if (!shader_part_validate(frag))
        return false;
    free(frag_src);

    GL(shader->id = glCreateProgram());
    GL(glAttachShader(shader->id, vert));
    GL(glAttachShader(shader->id, frag));
    GL(glLinkProgram(shader->id));
    if (!shader_validate(shader))
        return false;

    GL(glDeleteShader(vert));
    GL(glDeleteShader(frag));
    return true;
}

void shader_use(shader_t *shader)
{
    GL(glUseProgram(shader->id));
}

void shader_destroy(shader_t *shader)
{
    GL(glDeleteProgram(shader->id));
}

