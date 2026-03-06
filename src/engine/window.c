#include "engine/window.h"

#include "util/debug.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

static void framebuffer_size_callback(GLFWwindow *handle, int width, int height)
{
    GL(glViewport(0, 0, width, height));
    window_t *window = glfwGetWindowUserPointer(handle);
    window->width = width;
    window->height = height;
}

boolean window_create(window_t *window, int width, int height, const char *title)
{
    if (!glfwInit())
    {
        perror("ERROR::GLFW::INIT_FAIL");
        return false;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window->handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window->handle)
    {
        perror("ERROR::WINDOW::CREATE_FAIL");
        window_destroy(window);
        return false;
    }
    glfwMakeContextCurrent(window->handle);
    glfwSetWindowUserPointer(window->handle, window);
    glfwSetFramebufferSizeCallback(window->handle, framebuffer_size_callback);
    window->width = width;
    window->height = height;
    window->title = title;
    return true;
}

boolean window_should_close(window_t *window)
{
    return glfwWindowShouldClose(window->handle);
}

void window_swap_buffers(window_t *window)
{
    glfwSwapBuffers(window->handle);
    // glfwSwapInterval(1);
}

void window_poll_events()
{
    glfwPollEvents();
}

void window_destroy(window_t *window)
{
    glfwDestroyWindow(window->handle);
    glfwTerminate();
}


