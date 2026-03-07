#ifndef E_WINDOW_H
#define E_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "util/types.h"

void key_callback(GLFWwindow *handle, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *handle, double xpos, double ypos);
void scroll_callback(GLFWwindow *handle, double xoffset, double yoffset);

typedef struct
{
    GLFWwindow *handle;
    int width, height;
    const char *title;
} window_t;

// Creates a window and sets it as the OpenGL context.
boolean window_create(window_t *window, int width, int height, const char *title);

// Checks whether the window should close. Returns true
// when closing event has been triggered.
boolean window_should_close(window_t *window);

// Swap the windows buffers to display what has been drawn.
void window_swap_buffers(window_t *window);

// Polls for events like keyboard mouse input.
void window_poll_events(void);

// Destroys the window.
void window_destroy(window_t *window);

#endif
