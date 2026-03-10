#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer/renderer.h"
#include "engine/window.h"
//#include "renderer/index_buf.h"
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

#define WIN_WIDTH 1064
#define WIN_HEIGHT (3 * (WIN_WIDTH))/4

void push_verts(vert_buf *vb);

camera cam = { 0 };
vec3 cam_init_pos = { 0, 0, 3 };
float delta_time = .0f, last_frame = .0f;

vec3 light_pos = { 1.2, 1, 2 };

// Mouse input globals
float last_x = (float)WIN_WIDTH/2, last_y = (float)WIN_HEIGHT/2;
boolean mouse_first = true, mouse_invert = false;

int main()
{
    window_t window;
    ASSERTM(window_create(&window, WIN_WIDTH, WIN_HEIGHT, "C-GL"), "Window creation failed");
    renderer_init(&window);
    camera_create(&cam, cam_init_pos, 2.0f, 0.1f);

    shader_t obj_shader;
    ASSERTM(shader_create(&obj_shader, "res/shaders/obj.vert", "res/shaders/obj.frag"), "Object shader creation fail");

    shader_t lamp_shader;
    ASSERTM(shader_create(&lamp_shader, "res/shaders/lamp.vert", "res/shaders/lamp.frag"), 
            "Lighting shader creation fail");

    vert_array obj_va; va_create(&obj_va);
    vert_buf vb; vb_create(&vb);

    push_verts(&vb);
    // Position
    va_add_attrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(vert), (const void*)offsetof(vert, pos));
    // Normal 
    va_add_attrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(vert), (const void*)offsetof(vert, norm));
    vb_push_verts(&vb, GL_STATIC_DRAW);

    vert_array light_va; va_create(&light_va);
    vb_bind(&vb);
    va_add_attrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(vert), (const void*)offsetof(vert, pos));
 
    while (!window_should_close(&window))
    {
        float current_frame = (float)glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
        camera_move(&cam, delta_time);

        renderer_clear((solid_color){10, 10, 10});

        // Moving the lamp in a strange time varying curve 
        float xz_radius = 5;
        light_pos[0] = xz_radius * (float)cos(glfwGetTime());
        //light_pos[1] = 3 * (float)cos(3*glfwGetTime());
        light_pos[2] = xz_radius * (float)sin(glfwGetTime());

        shader_use(&obj_shader);
        mat4 model, view, proj;
        vec3 light_color = {
            sin(2 * glfwGetTime()),
            sin(0.7 * glfwGetTime()),
            sin(1.3 * glfwGetTime())
        };
        // vec3 light_color = {1,1,1};
        vec3 diffuse_color, ambient_color;
        glm_vec3_mul(light_color, (vec3){0.5,0.5,0.5}, diffuse_color);
        glm_vec3_mul(diffuse_color, (vec3){0.2,0.2,0.2}, ambient_color);
        glm_mat4_identity(model);
        camera_view_mat(&cam, view);
        glm_perspective(glm_rad(cam.zoom), (float)window.width/(float)window.height, 0.1f, 100.0f, proj);
        shader_set_fvec3(&obj_shader, "light.pos", light_pos);
        shader_set_fvec3(&obj_shader, "view_pos", cam.pos);
        shader_set_mat4(&obj_shader, "model", model);
        shader_set_mat4(&obj_shader, "view", view);
        shader_set_mat4(&obj_shader, "proj", proj);
        shader_set_fvec3(&obj_shader, "light.ambient",
                ambient_color);
        shader_set_fvec3(&obj_shader, "light.diffuse",
                diffuse_color);
        shader_set_fvec3(&obj_shader, "light.specular",
                (vec3){1,1,1});
        shader_set_fvec3(&obj_shader, "material.ambient",
                (vec3){0.0215,0.1745,0.0215});
        shader_set_fvec3(&obj_shader, "material.diffuse",
                (vec3){0.07568,0.61424,0.07568});
        shader_set_fvec3(&obj_shader, "material.specular",
                (vec3){0.633,0.727811,0.633});
        shader_set_float(&obj_shader, "material.shininess", 0.6 * 128);


        va_bind(&obj_va);
        renderer_draw_triangles(0, 36);

        // Light source 
        shader_use(&lamp_shader);
        glm_mat4_identity(model);
        glm_translate(model, light_pos);
        glm_scale(model, (vec3){0.2,0.2,0.2});
        shader_set_mat4(&lamp_shader, "model", model);
        shader_set_mat4(&lamp_shader, "view", view);
        shader_set_mat4(&lamp_shader, "proj", proj);

        va_bind(&light_va);
        renderer_draw_triangles(0, 36);

        window_swap_buffers(&window);
        window_poll_events();
    }

    va_destroy(&obj_va);
    va_destroy(&light_va);
    vb_destroy(&vb);
    window_destroy(&window);
}

void push_verts(vert_buf *vb)
{
    vertvec_push_list(&vb->verts, 36, 
            // Front face
            (vert){
            .pos = {-0.5f, -0.5f, -0.5f}, 
            .norm = {0.0f, 0.0f, -1.0f}
            },
            (vert){
            .pos = {0.5f, -0.5f, -0.5f}, 
            .norm = {0.0f, 0.0f, -1.0f}
            },
            (vert){
            .pos = {0.5f, 0.5f, -0.5f}, 
            .norm = {0.0f, 0.0f, -1.0f}
            },
            (vert){
            .pos = {0.5f, 0.5f, -0.5f}, 
            .norm = {0.0f, 0.0f, -1.0f}
            },
            (vert){
            .pos = {-0.5f, 0.5f, -0.5f}, 
            .norm = {0.0f, 0.0f, -1.0f}
            },
            (vert){
                .pos = {-0.5f, -0.5f, -0.5f}, 
                .norm = {0.0f, 0.0f, -1.0f}
            },

            // Back face
            (vert){
                .pos = {-0.5f, -0.5f, 0.5f}, 
                .norm = {0.0f, 0.0f, 1.0f}
            },
            (vert){
                .pos = {0.5f, -0.5f, 0.5f}, 
                .norm = {0.0f, 0.0f, 1.0f}
            },
            (vert){
                .pos = {0.5f, 0.5f, 0.5f}, 
                .norm = {0.0f, 0.0f, 1.0f}
            },
            (vert){
                .pos = {0.5f, 0.5f, 0.5f}, 
                .norm = {0.0f, 0.0f, 1.0f}
            },
            (vert){
                .pos = {-0.5f, 0.5f, 0.5f}, 
                .norm = {0.0f, 0.0f, 1.0f}
            },
            (vert){
                .pos = {-0.5f, -0.5f, 0.5f}, 
                .norm = {0.0f, 0.0f, 1.0f}
            },

            // Left face
            (vert){
                .pos = {-0.5f, 0.5f, 0.5f}, 
                .norm = {-1.0f, 0.0f, 0.0f}
            },
            (vert){
                .pos = {-0.5f, 0.5f, -0.5f}, 
                .norm = {-1.0f, 0.0f, 0.0f}
            },
            (vert){
                .pos = {-0.5f, -0.5f, -0.5f}, 
                .norm = {-1.0f, 0.0f, 0.0f}
            },
            (vert){
                .pos = {-0.5f, -0.5f, -0.5f}, 
                .norm = {-1.0f, 0.0f, 0.0f}
            },
            (vert){
                .pos = {-0.5f, -0.5f, 0.5f}, 
                .norm = {-1.0f, 0.0f, 0.0f}
            },
            (vert){
                .pos = {-0.5f, 0.5f, 0.5f}, 
                .norm = {-1.0f, 0.0f, 0.0f}
            },

            // Right face
            (vert){
                .pos = {0.5f, 0.5f, 0.5f}, 
                .norm = {1.0f, 0.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, 0.5f, -0.5f}, 
                .norm = {1.0f, 0.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, -0.5f, -0.5f}, 
                .norm = {1.0f, 0.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, -0.5f, -0.5f}, 
                .norm = {1.0f, 0.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, -0.5f, 0.5f}, 
                .norm = {1.0f, 0.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, 0.5f, 0.5f}, 
                .norm = {1.0f, 0.0f, 0.0f}
            },

            // Bottom face
            (vert){
                .pos = {-0.5f, -0.5f, -0.5f}, 
                .norm = {0.0f, -1.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, -0.5f, -0.5f}, 
                .norm = {0.0f, -1.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, -0.5f, 0.5f}, 
                .norm = {0.0f, -1.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, -0.5f, 0.5f}, 
                .norm = {0.0f, -1.0f, 0.0f}
            },
            (vert){
                .pos = {-0.5f, -0.5f, 0.5f}, 
                .norm = {0.0f, -1.0f, 0.0f}
            },
            (vert){
                .pos = {-0.5f, -0.5f, -0.5f}, 
                .norm = {0.0f, -1.0f, 0.0f}
            },

            // Top face
            (vert){
                .pos = {-0.5f, 0.5f, -0.5f}, 
                .norm = {0.0f, 1.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, 0.5f, -0.5f}, 
                .norm = {0.0f, 1.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, 0.5f, 0.5f}, 
                .norm = {0.0f, 1.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, 0.5f, 0.5f}, 
                .norm = {0.0f, 1.0f, 0.0f}
            },
            (vert){
                .pos = {-0.5f, 0.5f, 0.5f}, 
                .norm = {0.0f, 1.0f, 0.0f}
            },
            (vert){
                .pos = {-0.5f, 0.5f, -0.5f}, 
                .norm = {0.0f, 1.0f, 0.0f}
            });
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
