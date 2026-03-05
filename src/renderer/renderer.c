#include "renderer/renderer.h"
#include "util/debug.h"
#include "renderer/index_buf.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

bool renderer_init(window_t *window)
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        perror("ERROR::glad::GL_LOAD_FAIL");
        return false;
    }
    GL(glViewport(0, 0, window->width, window->height));
    return true;
}

void renderer_clear(bytevec3 color)
{
    GL(glClear(GL_COLOR_BUFFER_BIT));
    GL(glClearColor((float)color.x/255, (float)color.y/255, (float)color.z/255, 1.0f));
}

void renderer_draw_triangles(int first, int count)
{
    GL(glDrawArrays(GL_TRIANGLES, first, count));
}

void renderer_draw_elements(int mode, index_buf *ib)
{
    GL(glDrawElements(mode, ib->indices.length, GL_UNSIGNED_INT, 0));
}
