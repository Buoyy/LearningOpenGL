#include "renderer/renderer.h"
#include "engine/window.h"
#include "renderer/texture.h"
// #include "util/debug.h"
#include "renderer/shader.h"
#include "renderer/vert_array.h"
#include "renderer/vert_buf.h"
#include "renderer/index_buf.h"
#include "util/types.h"

#include <stb_image.h>

#include <math.h>
#include <stddef.h>
#include <stdbool.h>

int main()
{
    window_t window;
    if (!window_create(&window, 800, 600, "HALO"))
        return 1;
    renderer_init(&window);
 
    vert_array va; va_create(&va);
    vert_buf vb; vb_create(&vb);

    vertvec_push(&vb.verts, (vert){
        .pos = (vec2) {-0.5f, -0.5f},
        .color = (bytevec3) {255, 0, 0},
        .uv = (vec2) {0.0f, 0.0f}
            });
    vertvec_push(&vb.verts, (vert){
        .pos = (vec2) {0.5f, -0.5f},
        .color = (bytevec3) {0, 255, 0},
        .uv = (vec2) {1.0f, 0.0f}
            });
    vertvec_push(&vb.verts, (vert){
        .pos = (vec2) {0.5f, 0.5f},
        .color = (bytevec3) {0, 0, 255},
        .uv = (vec2) {1.0f, 1.0f}
            });
    vertvec_push(&vb.verts, (vert){
        .pos = (vec2) {-0.5f, 0.5f},
        .color = (bytevec3) {255, 0, 0},
        .uv = (vec2) {0.0f, 1.0f}
            });

    // Position 
    va_add_attrib(0, 2, GL_FLOAT, GL_FALSE, sizeof(vert), (void*)offsetof(vert, pos));
    // Color 
    va_add_attrib(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vert), (void*)offsetof(vert, color));
    // Texture Coords
    va_add_attrib(2, 2, GL_FLOAT, GL_FALSE, sizeof(vert), (void*)offsetof(vert, uv)); 
    
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
    texture_2d_param(GL_TEXTURE_WRAP_S, GL_REPEAT);
    texture_2d_param(GL_TEXTURE_WRAP_T, GL_REPEAT);
    texture_2d_param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture_2d_param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture_2d_load("res/textures/container.jpg", GL_RGB);

    texture_2d face; 
    texture_2d_create(&face, 1);
    texture_2d_param(GL_TEXTURE_WRAP_S, GL_REPEAT);
    texture_2d_param(GL_TEXTURE_WRAP_T, GL_REPEAT);
    texture_2d_param(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture_2d_param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture_2d_load("res/textures/awesomeface.png", GL_RGBA);

    shader_t shader;
    if (!shader_create(&shader, "res/shaders/basic.vert", "res/shaders/basic.frag"))
        return false;
    shader_use(&shader);
    shader_set_int(&shader, "tex1", 0);
    shader_set_int(&shader, "tex2", 1);

    while (!window_should_close(&window))
    {
        renderer_clear((bytevec3){50, 97, 97});

        float mix_amount = (sin(2*glfwGetTime())+1)/2;
        shader_set_float(&shader, "mix_amount", mix_amount);
        texture_2d_activate(&container);
        texture_2d_activate(&face);
        va_bind(&va);
        renderer_draw_elements(GL_TRIANGLES, &ib);

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
