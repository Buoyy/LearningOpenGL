#ifndef E_WINDOW_H
#define E_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdbool.h>

typedef struct
{
    GLFWwindow *handle;
    int width, height;
    const char *title;
} window_t;

// Creates a window and sets it as the OpenGL context.
bool window_create(window_t *window, int width, int height, const char *title);

// Checks whether the window should close. Returns true
// when closing event has been triggered.
bool window_should_close(window_t *window);

// Swap the windows buffers to display what has been drawn.
void window_swap_buffers(window_t *window);

// Polls for events like keyboard mouse input.
void window_poll_events(void);

// Destroys the window.
void window_destroy(window_t *window);

#endif
