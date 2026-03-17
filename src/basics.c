#include "renderer/index_buf.h"
#include "renderer/renderer.h"
#include "engine/window.h"
#include "engine/camera.h"
#include "renderer/texture.h"
//#include "util/debug.h"
#include "renderer/shader.h"
#include "renderer/vert_array.h"
#include "renderer/vert_buf.h"
//#include "renderer/index_buf.h"
#include "util/types.h"

#include <GLFW/glfw3.h>
#include <cglm/vec3.h>
#include <stb_image.h>
#include <cglm/cglm.h>

//#include <math.h>
#include <stddef.h>

#define WIN_WIDTH 960
#define WIN_HEIGHT 720

void push_verts(vert_buf *vb);
void push_indices(index_buf *ib);

camera cam = { 0 };
float delta_time = .0f, last_frame_time = .0f;

// Mouse input globals
float last_x = (float)WIN_WIDTH/2, last_y = (float)WIN_HEIGHT/2;
boolean mouse_first = true, mouse_invert = false;

int main()
{
    window_t window;
    if (!window_create(&window, WIN_WIDTH, WIN_HEIGHT, "HALO"))
return 1;
    renderer_init(&window);
    camera_create(&cam, (vec3){0,0,2}, 3.f, 0.05f);
    vert_array va; va_create(&va);
    vert_buf vb; vb_create(&vb);
    index_buf ib; ib_create(&ib);

    push_verts(&vb);
    push_indices(&ib);

    //vertvec_destroy(&vb.verts);
    //uivec_destroy(&ib.indices);

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

    // END.

    // Position 
    va_add_attrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(vert), (void*)offsetof(vert, pos));
    // Texture Coords
    va_add_attrib(1, 2, GL_FLOAT, GL_FALSE, sizeof(vert), (void*)offsetof(vert, uv)); 

    vb_push_verts(&vb, GL_STATIC_DRAW);
    ib_push_indices(&ib, GL_STATIC_DRAW);
    va_unbind();

    stbi_set_flip_vertically_on_load(true);
    texture_2d container; 
    texture_2d_create(&container, 0);
    texture_2d_params(&container, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
    texture_2d_load("res/textures/container.jpg", GL_RGB);

    texture_2d face; 
    texture_2d_create(&face, 1);
    texture_2d_params(&face, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
    texture_2d_load("res/textures/awesomeface.png", GL_RGBA);

    shader_t shader;
    if (!shader_create(&shader, "res/shaders/basic.vert", "res/shaders/basic.frag"))
        return false;
    shader_use(&shader);
    shader_set_int(&shader, "tex1", 0);
    shader_set_int(&shader, "tex2", 1);

    while (!window_should_close(&window))
    {
        float current_frame_time = glfwGetTime();
        delta_time = current_frame_time - last_frame_time;
        last_frame_time = current_frame_time;
        camera_move(&cam, delta_time);

        renderer_clear((solid_color){50, 97, 97});

        texture_2d_activate(&container);
        texture_2d_activate(&face);

        mat4 view; camera_view_mat(&cam, view);
        shader_set_mat4(&shader, "view", view);

        mat4 proj;
        glm_perspective(glm_rad(cam.zoom), (float)window.width/(float)window.height, .1f, 100.0f, proj);
        shader_set_mat4(&shader, "projection", proj);


        shader_use(&shader);
        va_bind(&va);
        for (uint i = 0; i < 10; ++i)
        {
            mat4 model; glm_mat4_identity(model);
            glm_translate(model, cube_pos[i]);
            vec3 rot_axis;
              if (i%2 == 0)
              {
              glm_vec3_copy((vec3){1,0.3,0}, rot_axis);
              glm_rotate(model, (float)glfwGetTime(), rot_axis);
              }
              else //if (i%3 == 0)
              {
              glm_vec3_copy((vec3){0.3,0.1,0.5}, rot_axis);
              glm_rotate(model, (float)2*glfwGetTime(), rot_axis);
              }
            shader_set_mat4(&shader, "model", model);

            renderer_draw_elements(GL_TRIANGLES, &ib);
        }

        window_swap_buffers(&window);
        window_poll_events();
    }

    // Final destruction, hell yeah.

    texture_2d_destroy(&container);
    texture_2d_destroy(&face);
    ib_destroy(&ib);
    vb_destroy(&vb);
    va_destroy(&va);
    shader_destroy(&shader);
    window_destroy(&window);
    return 0;
}

void push_verts(vert_buf *vb)
{
    // VERT PUSHER HELL YEAHH. START!
    vertvec_push_list(&vb->verts, 24,
            // Front face
            (vert) {
            .pos = {-0.5f, -0.5f, 0.5f},
            .uv = {0, 0}
            }, 
            (vert) {
            .pos = {0.5f, -0.5f, 0.5f},
            .uv = {1, 0} 
            },
            (vert) {
            .pos = {0.5f, 0.5f, 0.5f},
            .uv = {1, 1} 
            },
            (vert) {
            .pos = {-0.5f, 0.5f, 0.5f},
            .uv = {0, 1} 
            },

            // Top face
            (vert) {
                .pos = {-0.5f, 0.5f, 0.5f},
                .uv = {0, 0} 
            },
            (vert) {
                .pos = {0.5f, 0.5f, 0.5f},
                .uv = {1, 0} 
            },
            (vert) {
                .pos = {0.5f, 0.5f, -0.5f},
                .uv = {1, 1} 
            },
            (vert) {
                .pos = {-0.5f, 0.5f, -0.5f},
                .uv = {0, 1} 
            },

            // Back face
            (vert) {
                .pos = {-0.5f, -0.5f, -0.5f},
                .uv = {0, 0} 
            },
            (vert) {
                .pos = {0.5f, -0.5f, -0.5f},
                .uv = {1, 0} 
            },
            (vert) {
                .pos = {0.5f, 0.5f, -0.5f},
                .uv = {1, 1} 
            },
            (vert) {
                .pos = {-0.5f, 0.5f, -0.5f},
                .uv = {0, 1} 
            },

            // Bottom face
            (vert) {
                .pos = {-0.5f, -0.5f, -0.5f},
                .uv = {0, 0} 
            },
            (vert) {
                .pos = {0.5f, -0.5f, -0.5f},
                .uv = {1, 0} 
            },
            (vert) {
                .pos = {0.5f, -0.5f, 0.5f},
                .uv = {1, 1} 
            },
            (vert) {
                .pos = {-0.5f, -0.5f, 0.5f},
                .uv = {0, 1} 
            },

            // Left face
            (vert) {
                .pos = {-0.5f, -0.5f, -0.5f},
                .uv = {0, 0} 
            },
            (vert) {
                .pos = {-0.5f, -0.5f, 0.5f},
                .uv = {1, 0} 
            },
            (vert) {
                .pos = {-0.5f, 0.5f, 0.5f},
                .uv = {1, 1} 
            },
            (vert) {
                .pos = {-0.5f, 0.5f, -0.5f},
                .uv = {0, 1} 
            },

            // Right face
            (vert) {
                .pos = {0.5f, -0.5f, 0.5f},
                .uv = {0, 0} 
            },
            (vert) {
                .pos = {0.5f, -0.5f, -0.5f},
                .uv = {1, 0} 
            },
            (vert) {
                .pos = {0.5f, 0.5f, -0.5f},
                .uv = {1, 1} 
            },
            (vert) {
                .pos = {0.5f, 0.5f, 0.5f},
                .uv = {0, 1} 
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
