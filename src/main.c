#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer/renderer.h"
#include "engine/window.h"
#include "renderer/index_buf.h"
#include "engine/camera.h"
//#include "util/debug.h"
#include "renderer/shader.h"
#include "renderer/vert_array.h"
#include "renderer/vert_buf.h"
//#include "renderer/index_buf.h"
#include "util/types.h"

#include <stb_image.h>
#include <cglm/cglm.h>

//#include <math.h>
#include <stddef.h>

#define WIN_WIDTH 960
#define WIN_HEIGHT 720

void push_verts(vert_buf *vb);
void push_indices(index_buf *ib);

camera cam = { 0 };
vec3 cam_init_pos = { 0, 0.3, 3 };
float delta_time = .0f, last_frame = .0f;

vec3 light_pos = { 1.2, 3, 2 };

// Mouse input globals
float last_x = (float)WIN_WIDTH/2, last_y = (float)WIN_HEIGHT/2;
boolean mouse_first = true, mouse_invert = false;

int main()
{
    window_t window;
    ASSERTM(window_create(&window, WIN_WIDTH, WIN_HEIGHT, "C-GL"), "Window creation failed");
    renderer_init(&window);
    camera_create(&cam, cam_init_pos, 2.0f, 0.1f);

    shader_t basic_shader;
    ASSERTM(shader_create(&basic_shader, "res/shaders/basic.vert", "res/shaders/basic.frag"), "Basic shader creation fail");

    shader_t light_src_shader;
    ASSERTM(shader_create(&light_src_shader, "res/shaders/light.vert", "res/shaders/light.frag"), 
            "Lighting shader creation fail");

    vert_array obj_va; va_create(&obj_va);
    vert_buf vb; vb_create(&vb);
    index_buf ib; ib_create(&ib);

    push_verts(&vb); push_indices(&ib);
    // Position
    va_add_attrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(vert), (const void*)offsetof(vert, pos));
    vb_push_verts(&vb, GL_STATIC_DRAW);
    ib_push_indices(&ib, GL_STATIC_DRAW);


    vert_array light_va; va_create(&light_va);
    vb_bind(&vb); ib_bind(&ib);
    va_add_attrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(vert), (const void*)offsetof(vert, pos));
 
    while (!window_should_close(&window))
    {
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
        camera_move(&cam, delta_time);

        renderer_clear((solid_color){10, 10, 10});
        
        // Object 
        shader_use(&basic_shader);
        shader_set_float3(&basic_shader, "light_color", 1.0f, 1.0f, 1.0f);
        shader_set_float3(&basic_shader, "obj_color", 0.3f, 0.0f, 0.3f);
        mat4 model, view, proj;
        glm_mat4_identity(model);
        camera_view_mat(&cam, view);
        glm_perspective(glm_rad(cam.zoom), (float)window.width/(float)window.height, 0.1f, 100.0f, proj);
        shader_set_mat4(&basic_shader, "model", model);
        shader_set_mat4(&basic_shader, "view", view);
        shader_set_mat4(&basic_shader, "proj", proj);

        va_bind(&obj_va);
        renderer_draw_elements(GL_TRIANGLES, &ib);

        // Light source 
        shader_use(&light_src_shader);
        glm_mat4_identity(model);
        glm_translate(model, light_pos);
        glm_scale(model, (vec3){0.2,0.2,0.2});
        shader_set_mat4(&light_src_shader, "model", model);
        shader_set_mat4(&light_src_shader, "view", view);
        shader_set_mat4(&light_src_shader, "proj", proj);

        va_bind(&light_va);
        renderer_draw_elements(GL_TRIANGLES, &ib);

        window_swap_buffers(&window);
        window_poll_events();
    }

    va_destroy(&obj_va);
    va_destroy(&light_va);
    ib_destroy(&ib);
    vb_destroy(&vb);
    window_destroy(&window);
}

void push_verts(vert_buf *vb)
{
    // VERT PUSHER HELL YEAHH. START!
    vertvec_push_list(&vb->verts, 24,
            // Front face
            (vert) {
            .pos = {-0.5f, -0.5f, 0.5f}
            }, 
            (vert) {
            .pos = {0.5f, -0.5f, 0.5f}
            },
            (vert) {
            .pos = {0.5f, 0.5f, 0.5f}
            },
            (vert) {
            .pos = {-0.5f, 0.5f, 0.5f}
            },

            // Top face
            (vert) {
            .pos = {-0.5f, 0.5f, 0.5f}
            },
            (vert) {
            .pos = {0.5f, 0.5f, 0.5f}
            },
            (vert) {
                .pos = {0.5f, 0.5f, -0.5f}
            },
            (vert) {
                .pos = {-0.5f, 0.5f, -0.5f}
            },

            // Back face
            (vert) {
                .pos = {-0.5f, -0.5f, -0.5f}
            },
            (vert) {
                .pos = {0.5f, -0.5f, -0.5f}
            },
            (vert) {
                .pos = {0.5f, 0.5f, -0.5f}
            },
            (vert) {
                .pos = {-0.5f, 0.5f, -0.5f}
            },

            // Bottom face
            (vert) {
                .pos = {-0.5f, -0.5f, -0.5f}
            },
            (vert) {
                .pos = {0.5f, -0.5f, -0.5f}
            },
            (vert) {
                .pos = {0.5f, -0.5f, 0.5f}
            },
            (vert) {
                .pos = {-0.5f, -0.5f, 0.5f}
            },

            // Left face
            (vert) {
                .pos = {-0.5f, -0.5f, -0.5f}
            },
            (vert) {
                .pos = {-0.5f, -0.5f, 0.5f}
            },
            (vert) {
                .pos = {-0.5f, 0.5f, 0.5f}
            },
            (vert) {
                .pos = {-0.5f, 0.5f, -0.5f}
            },

            // Right face
            (vert) {
                .pos = {0.5f, -0.5f, 0.5f}
            },
            (vert) {
                .pos = {0.5f, -0.5f, -0.5f},
            },
            (vert) {
                .pos = {0.5f, 0.5f, -0.5f},
            },
            (vert) {
                .pos = {0.5f, 0.5f, 0.5f},
            });
}

void push_indices(index_buf *ib)
{
    uivec_push_list(&ib->indices, 36,
            // Front face
            0, 1, 2,
            2, 3, 0,
            // Top face
            4, 5, 6,
            6, 7, 4,
            // Back face
            8, 9, 10,
            10, 11, 8,
            // Bottom face
            12, 13, 14,
            14, 15, 12,
            // Left face
            16, 17, 18,
            18, 19, 16,
            // Right face
            20, 21, 22,
            22, 23, 20 );
}

void key_callback(GLFWwindow *handle, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;

    if (action != GLFW_PRESS) return;

    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(handle, true);

    if (key == GLFW_KEY_UP || key == GLFW_KEY_W)
        camera_process_keyboard(&cam, CAMERA_MOVE_FORWARD);
    if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S)
        camera_process_keyboard(&cam, CAMERA_MOVE_BACKWARD);
    if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) 
        camera_process_keyboard(&cam, CAMERA_MOVE_LEFT);
    if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D)
        camera_process_keyboard(&cam, CAMERA_MOVE_RIGHT);

    if (key == GLFW_KEY_SPACE)
        camera_process_keyboard(&cam, CAMERA_MOVE_UP);
    if (key == GLFW_KEY_LEFT_CONTROL)
        camera_process_keyboard(&cam, CAMERA_MOVE_DOWN);

    if (key == GLFW_KEY_R)
        glm_vec3_copy(cam_init_pos, cam.pos);
}

void mouse_callback(GLFWwindow *handle, double xpos, double ypos)
{
    if (mouse_first)
    {
        last_x = (float)xpos;
        last_y = (float)ypos;
        mouse_first = false;
    }
    float delta_x = xpos - last_x;
    float delta_y = (mouse_invert) ? -(last_y - ypos) : (last_y - ypos);
    last_x = (float)xpos;
    last_y = (float)ypos;
    camera_process_mouse_move(&cam, delta_x, delta_y, true);
    (void)handle;
}

void scroll_callback(GLFWwindow *handle, double xoffset, double yoffset)
{
    camera_process_mouse_scroll(&cam, yoffset);
    printf("%.2f\n", cam.zoom);
    (void)handle; (void)xoffset;
}
