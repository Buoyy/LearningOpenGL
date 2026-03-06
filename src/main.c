#include "renderer/renderer.h"
#include "engine/window.h"
#include "renderer/texture.h"
//#include "util/debug.h"
#include "renderer/shader.h"
#include "renderer/vert_array.h"
#include "renderer/vert_buf.h"
#include "renderer/index_buf.h"
#include "util/types.h"

#include <cglm/vec3.h>
#include <stb_image.h>
#include <cglm/cglm.h>

//#include <math.h>
#include <stddef.h>

int main()
{
    window_t window;
    if (!window_create(&window, 800, 600, "HALO"))
        return 1;
    renderer_init(&window);

    vert_array va; va_create(&va);
    vert_buf vb; vb_create(&vb);

    // VERT PUSHER HELL YEAHH. START!

    vertvec_push_list(&vb.verts, 36, 
            (vert){
            .pos = {-0.5f, -0.5f, -0.5f}, 
            .uv = {0.0f, 0.0f}
        },
            (vert){
            .pos = {0.5f, -0.5f, -0.5f}, 
            .uv = {1.0f, 0.0f}
        },
            (vert){
            .pos = {0.5f, 0.5f, -0.5f}, 
            .uv = {1.0f, 1.0f}
        },
            (vert){
            .pos = {0.5f, 0.5f, -0.5f}, 
            .uv = {1.0f, 1.0f}
        },
            (vert){
            .pos = {-0.5f, 0.5f, -0.5f}, 
            .uv = {0.0f, 1.0f}
        },
            (vert){
                .pos = {-0.5f, -0.5f, -0.5f}, 
                .uv = {0.0f, 0.0f}
        },
            (vert){
                .pos = {-0.5f, -0.5f, 0.5f}, 
                .uv = {0.0f, 0.0f}
        },
            (vert){
                .pos = {0.5f, -0.5f, 0.5f}, 
                .uv = {1.0f, 0.0f}
        },
            (vert){
                .pos = {0.5f, 0.5f, 0.5f}, 
                .uv = {1.0f, 1.0f}
        },
            (vert){
                .pos = {0.5f, 0.5f, 0.5f}, 
                .uv = {1.0f, 1.0f}
        },
            (vert){
                .pos = {-0.5f, 0.5f, 0.5f}, 
                .uv = {0.0f, 1.0f}
        },
            (vert){
                .pos = {-0.5f, -0.5f, 0.5f}, 
                .uv = {0.0f, 0.0f}
        },
            (vert){
                .pos = {-0.5f, 0.5f, 0.5f}, 
                .uv = {1.0f, 0.0f}
        },
            (vert){
                .pos = {-0.5f, 0.5f, -0.5f}, 
                .uv = {1.0f, 1.0f}
        },
            (vert){
                .pos = {-0.5f, -0.5f, -0.5f}, 
                .uv = {0.0f, 1.0f}
        },
            (vert){
                .pos = {-0.5f, -0.5f, -0.5f}, 
                .uv = {0.0f, 1.0f}
        },
            (vert){
                .pos = {-0.5f, -0.5f, 0.5f}, 
                .uv = {0.0f, 0.0f}
        },
            (vert){
                .pos = {-0.5f, 0.5f, 0.5f}, 
                .uv = {1.0f, 0.0f}
        },
            (vert){
                .pos = {0.5f, 0.5f, 0.5f}, 
                .uv = {1.0f, 0.0f}
        },
            (vert){
                .pos = {0.5f, 0.5f, -0.5f}, 
                .uv = {1.0f, 1.0f}
        },
            (vert){
                .pos = {0.5f, -0.5f, -0.5f}, 
                .uv = {0.0f, 1.0f}
        },
            (vert){
                .pos = {0.5f, -0.5f, -0.5f}, 
                .uv = {0.0f, 1.0f}
        },
            (vert){
                .pos = {0.5f, -0.5f, 0.5f}, 
                .uv = {0.0f, 0.0f}
        },
            (vert){
                .pos = {0.5f, 0.5f, 0.5f}, 
                .uv = {1.0f, 0.0f}
        },
            (vert){
                .pos = {-0.5f, -0.5f, -0.5f}, 
                .uv = {0.0f, 1.0f}
        },
            (vert){
                .pos = {0.5f, -0.5f, -0.5f}, 
                .uv = {1.0f, 1.0f}
        },
            (vert){
                .pos = {0.5f, -0.5f, 0.5f}, 
                .uv = {1.0f, 0.0f}
            },
            (vert){
                .pos = {0.5f, -0.5f, 0.5f}, 
                .uv = {1.0f, 0.0f}
        },
            (vert){
                .pos = {-0.5f, -0.5f, 0.5f}, 
                .uv = {0.0f, 0.0f}
        },
            (vert){
                .pos = {-0.5f, -0.5f, -0.5f}, 
                .uv = {0.0f, 1.0f}
        },
            (vert){
                .pos = {-0.5f, 0.5f, -0.5f}, 
                .uv = {0.0f, 1.0f}
        },
            (vert){
                .pos = {0.5f, 0.5f, -0.5f}, 
                .uv = {1.0f, 1.0f}
        },
            (vert){
                .pos = {0.5f, 0.5f, 0.5f}, 
                .uv = {1.0f, 0.0f}
        },
            (vert){
                .pos = {0.5f, 0.5f, 0.5f}, 
                .uv = {1.0f, 0.0f}
        },
            (vert){
                .pos = {-0.5f, 0.5f, 0.5f}, 
                .uv = {0.0f, 0.0f}
        },
            (vert){
                .pos = {-0.5f, 0.5f, -0.5f}, 
                .uv = {0.0f, 1.0f}
        });

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

    index_buf ib; ib_create(&ib);
    uivec_push_list(&ib.indices, 6,
            0, 1, 2,
            2, 0, 3);

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

    vec3 rot_axis = {1, 0.5, 0};
    glm_normalize(rot_axis);

    while (!window_should_close(&window))
    {
        renderer_clear((solid_color){50, 97, 97});

        texture_2d_activate(&container);
        texture_2d_activate(&face);

        mat4 view; glm_mat4_identity(view);
        mat4 proj; glm_mat4_identity(proj);
        glm_translate(view, (vec3){0,0,-3});
        float aspect = (float)window.width/window.height;
        glm_perspective(glm_rad(45), aspect, .1f, 100.0f, proj);

        shader_use(&shader);
        shader_set_mat4(&shader, "view", view);
        shader_set_mat4(&shader, "projection", proj);

        va_bind(&va);
        for (uint i = 0; i < 10; ++i)
        {
            mat4 model; glm_mat4_identity(model);
            glm_translate(model, cube_pos[i]);
            vec3 rot_axis;
            if (i%2 == 0)
                glm_vec3_copy((vec3){1,0.3,0}, rot_axis);
            else if (i%3 == 0)
                glm_vec3_copy((vec3){0.3,0.1,0.5}, rot_axis);
            glm_rotate(model, (float)glfwGetTime(), rot_axis);
            shader_set_mat4(&shader, "model", model);

            renderer_draw_triangles(0, 36);
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
