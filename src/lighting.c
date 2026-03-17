#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer/renderer.h"
#include "engine/window.h"
#include "engine/camera.h"
//#include "util/debug.h"
#include "renderer/shader.h"
#include "renderer/vert_array.h"
#include "renderer/vert_buf.h"
#include "renderer/texture.h"
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

vec3 light_dir      = { -0.2, -1.0, -0.3 };
vec3 pt_light_ambient  = { 0.05, 0.05, 0.05 };
vec3 pt_light_diffuse  = { 0.7, 0.7, 0.7 };
vec3 pt_light_specular = { 1.0, 1.0, 1.0 };
vec3 dir_light_ambient  = { 0.05, 0.05, 0.05 };
vec3 dir_light_diffuse  = { 0.6171, 0.5273, 0.125 };
vec3 dir_light_specular = { 0.55, 0.55, 0.55 };

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
    vec3 cube_pos[] = {
        {0.0f,  0.0f,  0.0f}, 
        {2.0f,  5.0f, -15.0f}, 
        {-1.5f, -2.2f, -2.5f},  
        {-3.8f, -2.0f, -12.3f},  
        {2.4f, -0.4f, -3.5f},  
        {-1.7f,  3.0f, -7.5f},  
        {1.3f, -2.0f, -2.5f},  
        {1.5f,  2.0f, -2.5f}, 
        {1.5f,  0.2f, -1.5f}, 
        {-1.3f,  1.0f, -1.5f} };

    vec3 light_pos[] = {
        {0.7, 0.2, 2.0},
        {2.3, -3.3, 4.0},
        {-4.0, 2.0, -12.0},
        {0.0, 0.0, -3.0}
    };

    // Position
    va_add_attrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(vert), (const void*)offsetof(vert, pos));
    // Normal 
    va_add_attrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(vert), (const void*)offsetof(vert, norm));
    vb_push_verts(&vb, GL_STATIC_DRAW);
    va_add_attrib(2, 2, GL_FLOAT, GL_FALSE, sizeof(vert), (const void*)offsetof(vert, uv));

    vert_array light_va; va_create(&light_va);
    vb_bind(&vb);
    va_add_attrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(vert), (const void*)offsetof(vert, pos));

    texture_2d diff_map, spec_map;
    texture_2d_create_default(&diff_map, 0,
        "res/textures/container2.png", GL_RGBA);
    texture_2d_create_default(&spec_map, 1,
        "res/textures/container2_spec.png", GL_RGBA);

    // All the settings for lighting 
    shader_use(&obj_shader);

    // Material
    shader_set_int(&obj_shader, "material.diffuse", 0);
    shader_set_int(&obj_shader, "material.specular", 1);
    shader_set_float(&obj_shader, "material.shininess", 64);
    
    // Attenuation parameters 
    // Light 0 
    shader_set_fvec3(&obj_shader, "pt_lights[0].position", light_pos[0]);
    shader_set_fvec3(&obj_shader, "pt_lights[0].ambient", pt_light_ambient);
    shader_set_fvec3(&obj_shader, "pt_lights[0].diffuse", pt_light_diffuse);
    shader_set_fvec3(&obj_shader, "pt_lights[0].specular", pt_light_specular);
    shader_set_float(&obj_shader, "pt_lights[0].att_const", 1.0f);
    shader_set_float(&obj_shader, "pt_lights[0].att_linear", 0.09f);
    shader_set_float(&obj_shader, "pt_lights[0].att_quadr", 0.032f);

    // Light 1
    shader_set_fvec3(&obj_shader, "pt_lights[1].position", light_pos[1]);
    shader_set_fvec3(&obj_shader, "pt_lights[1].ambient", pt_light_ambient);
    shader_set_fvec3(&obj_shader, "pt_lights[1].diffuse", pt_light_diffuse);
    shader_set_fvec3(&obj_shader, "pt_lights[1].specular", pt_light_specular);
    shader_set_float(&obj_shader, "pt_lights[1].att_const", 1.0f);
    shader_set_float(&obj_shader, "pt_lights[1].att_linear", 0.09f);
    shader_set_float(&obj_shader, "pt_lights[1].att_quadr", 0.032f);

    // Light 2
    shader_set_fvec3(&obj_shader, "pt_lights[2].position", light_pos[2]);
    shader_set_fvec3(&obj_shader, "pt_lights[2].ambient", pt_light_ambient);
    shader_set_fvec3(&obj_shader, "pt_lights[2].diffuse", pt_light_diffuse);
    shader_set_fvec3(&obj_shader, "pt_lights[2].specular", pt_light_specular);
    shader_set_float(&obj_shader, "pt_lights[2].att_const", 1.0f);
    shader_set_float(&obj_shader, "pt_lights[2].att_linear", 0.09f);
    shader_set_float(&obj_shader, "pt_lights[2].att_quadr", 0.032f);

    // Light 3
    shader_set_fvec3(&obj_shader, "pt_lights[3].position", light_pos[3]);
    shader_set_fvec3(&obj_shader, "pt_lights[3].ambient", pt_light_ambient);
    shader_set_fvec3(&obj_shader, "pt_lights[3].diffuse", pt_light_diffuse);
    shader_set_fvec3(&obj_shader, "pt_lights[3].specular", pt_light_specular);
    shader_set_float(&obj_shader, "pt_lights[3].att_const", 1.0f);
    shader_set_float(&obj_shader, "pt_lights[3].att_linear", 0.09f);
    shader_set_float(&obj_shader, "pt_lights[3].att_quadr", 0.032f);

    // Directional light setup 
    shader_set_fvec3(&obj_shader, "dir_light.direction", light_dir);
    shader_set_fvec3(&obj_shader, "dir_light.ambient", dir_light_ambient);
    shader_set_fvec3(&obj_shader, "dir_light.diffuse", dir_light_diffuse);
    shader_set_fvec3(&obj_shader, "dir_light.specular", dir_light_specular);
    
    while (!window_should_close(&window))
    {
        float current_frame = (float)glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
        camera_move(&cam, delta_time);

        renderer_clear((solid_color){20, 20, 20});

        shader_use(&obj_shader);
        mat4 model, view, proj;
        /*vec3 light_color = {
          sin(2 * glfwGetTime()),
          sin(0.7 * glfwGetTime()),
          sin(1.3 * glfwGetTime())
          };

          vec3 diffuse_color, ambient_color;
          glm_vec3_mul(light_color, (vec3){0.5,0.5,0.5}, diffuse_color);
          glm_vec3_mul(diffuse_color, (vec3){0.2,0.2,0.2}, ambient_color);*/
        glm_mat4_identity(model);
        camera_view_mat(&cam, view);
        glm_perspective(glm_rad(cam.zoom), (float)window.width/(float)window.height, 0.1f, 100.0f, proj);
        //shader_set_fvec3(&obj_shader, "d_light.direction", light_dir);
        shader_set_fvec3(&obj_shader, "view_pos", cam.pos);
        shader_set_mat4(&obj_shader, "model", model);
        shader_set_mat4(&obj_shader, "view", view);
        shader_set_mat4(&obj_shader, "proj", proj);
        shader_set_float(&obj_shader, "material.shininess", 32);
        texture_2d_activate(&diff_map);

        va_bind(&obj_va);
        for (uint i = 0; i < 10; ++i)
        {
            glm_mat4_identity(model);
            glm_translate(model, cube_pos[i]);
            float angle = 20.0f * i;
            glm_rotate(model, glm_rad(angle), (vec3){1, 0.3, 0.5});
            shader_set_mat4(&obj_shader, "model", model);
            renderer_draw_triangles(0, 36);
        }

        //Light source 
        shader_use(&lamp_shader);
        shader_set_mat4(&lamp_shader, "view", view);
        shader_set_mat4(&lamp_shader, "proj", proj);
        va_bind(&light_va);
        for (uint i = 0; i < 4; ++i)
        {
            glm_mat4_identity(model);
            glm_translate(model, light_pos[i]);
            glm_scale(model, (vec3){0.2,0.2,0.2});
            shader_set_mat4(&lamp_shader, "model", model);
            renderer_draw_triangles(0, 36);
        }

        window_swap_buffers(&window);
        window_poll_events();
    }

    va_destroy(&obj_va);
    va_destroy(&light_va);
    vb_destroy(&vb);
    shader_destroy(&obj_shader);
    shader_destroy(&lamp_shader);
    window_destroy(&window);
}

void push_verts(vert_buf *vb)
{
    vertvec_push_list(&vb->verts, 36,
            // Front face
            (vert){
            .pos = {-0.5f, -0.5f, -0.5f},
            .norm = {0.0f, 0.0f, -1.0f},
            .uv = {0.0f, 0.0f}
            },
            (vert){
            .pos = {0.5f, -0.5f, -0.5f},
            .norm = {0.0f, 0.0f, -1.0f},
            .uv = {1.0f, 0.0f}
            },
            (vert){
            .pos = {0.5f, 0.5f, -0.5f},
            .norm = {0.0f, 0.0f, -1.0f},
            .uv = {1.0f, 1.0f}
            },
            (vert){
            .pos = {0.5f, 0.5f, -0.5f},
            .norm = {0.0f, 0.0f, -1.0f},
            .uv = {1.0f, 1.0f}
            },
            (vert){
                .pos = {-0.5f, 0.5f, -0.5f},
                .norm = {0.0f, 0.0f, -1.0f},
                .uv = {0.0f, 1.0f}
            },
            (vert){
                .pos = {-0.5f, -0.5f, -0.5f},
                .norm = {0.0f, 0.0f, -1.0f},
                .uv = {0.0f, 0.0f}
            },
            // Back face
            (vert){
                .pos = {-0.5f, -0.5f, 0.5f},
                .norm = {0.0f, 0.0f, 1.0f},
                .uv = {0.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, -0.5f, 0.5f},
                .norm = {0.0f, 0.0f, 1.0f},
                .uv = {1.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, 0.5f, 0.5f},
                .norm = {0.0f, 0.0f, 1.0f},
                .uv = {1.0f, 1.0f}
            },
            (vert){
                .pos = {0.5f, 0.5f, 0.5f},
                .norm = {0.0f, 0.0f, 1.0f},
                .uv = {1.0f, 1.0f}
            },
            (vert){
                .pos = {-0.5f, 0.5f, 0.5f},
                .norm = {0.0f, 0.0f, 1.0f},
                .uv = {0.0f, 1.0f}
            },
            (vert){
                .pos = {-0.5f, -0.5f, 0.5f},
                .norm = {0.0f, 0.0f, 1.0f},
                .uv = {0.0f, 0.0f}
            },
            // Left face
            (vert){
                .pos = {-0.5f, 0.5f, 0.5f},
                .norm = {-1.0f, 0.0f, 0.0f},
                .uv = {1.0f, 0.0f}
            },
            (vert){
                .pos = {-0.5f, 0.5f, -0.5f},
                .norm = {-1.0f, 0.0f, 0.0f},
                .uv = {1.0f, 1.0f}
            },
            (vert){
                .pos = {-0.5f, -0.5f, -0.5f},
                .norm = {-1.0f, 0.0f, 0.0f},
                .uv = {0.0f, 1.0f}
            },
            (vert){
                .pos = {-0.5f, -0.5f, -0.5f},
                .norm = {-1.0f, 0.0f, 0.0f},
                .uv = {0.0f, 1.0f}
            },
            (vert){
                .pos = {-0.5f, -0.5f, 0.5f},
                .norm = {-1.0f, 0.0f, 0.0f},
                .uv = {0.0f, 0.0f}
            },
            (vert){
                .pos = {-0.5f, 0.5f, 0.5f},
                .norm = {-1.0f, 0.0f, 0.0f},
                .uv = {1.0f, 0.0f}
            },
            // Right face
            (vert){
                .pos = {0.5f, 0.5f, 0.5f},
                .norm = {1.0f, 0.0f, 0.0f},
                .uv = {1.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, 0.5f, -0.5f},
                .norm = {1.0f, 0.0f, 0.0f},
                .uv = {1.0f, 1.0f}
            },
            (vert){
                .pos = {0.5f, -0.5f, -0.5f},
                .norm = {1.0f, 0.0f, 0.0f},
                .uv = {0.0f, 1.0f}
            },
            (vert){
                .pos = {0.5f, -0.5f, -0.5f},
                .norm = {1.0f, 0.0f, 0.0f},
                .uv = {0.0f, 1.0f}
            },
            (vert){
                .pos = {0.5f, -0.5f, 0.5f},
                .norm = {1.0f, 0.0f, 0.0f},
                .uv = {0.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, 0.5f, 0.5f},
                .norm = {1.0f, 0.0f, 0.0f},
                .uv = {1.0f, 0.0f}
            },
            // Bottom face
            (vert){
                .pos = {-0.5f, -0.5f, -0.5f},
                .norm = {0.0f, -1.0f, 0.0f},
                .uv = {0.0f, 1.0f}
            },
            (vert){
                .pos = {0.5f, -0.5f, -0.5f},
                .norm = {0.0f, -1.0f, 0.0f},
                .uv = {1.0f, 1.0f}
            },
            (vert){
                .pos = {0.5f, -0.5f, 0.5f},
                .norm = {0.0f, -1.0f, 0.0f},
                .uv = {1.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, -0.5f, 0.5f},
                .norm = {0.0f, -1.0f, 0.0f},
                .uv = {1.0f, 0.0f}
            },
            (vert){
                .pos = {-0.5f, -0.5f, 0.5f},
                .norm = {0.0f, -1.0f, 0.0f},
                .uv = {0.0f, 0.0f}
            },
            (vert){
                .pos = {-0.5f, -0.5f, -0.5f},
                .norm = {0.0f, -1.0f, 0.0f},
                .uv = {0.0f, 1.0f}
            },
            // Top face 
            (vert){
                .pos = {-0.5f, 0.5f, -0.5f},
                .norm = {0.0f, 1.0f, 0.0f},
                .uv = {0.0f, 1.0f}
            },
            (vert){
                .pos = {0.5f, 0.5f, -0.5f},
                .norm = {0.0f, 1.0f, 0.0f},
                .uv = {1.0f, 1.0f}
            },
            (vert){
                .pos = {0.5f, 0.5f, 0.5f},
                .norm = {0.0f, 1.0f, 0.0f},
                .uv = {1.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, 0.5f, 0.5f},
                .norm = {0.0f, 1.0f, 0.0f},
                .uv = {1.0f, 0.0f}
            },
            (vert){
                .pos = {-0.5f, 0.5f, 0.5f},
                .norm = {0.0f, 1.0f, 0.0f},
                .uv = {0.0f, 0.0f}
            },
            (vert){
                .pos = {-0.5f, 0.5f, -0.5f},
                .norm = {0.0f, 1.0f, 0.0f},
                .uv = {0.0f, 1.0f}
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
