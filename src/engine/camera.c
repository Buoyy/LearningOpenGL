#include "engine/camera.h"

#include <cglm/cglm.h>
#include <math.h>

void camera_create(camera *cam, float *pos, float speed, float sens)
{
    glm_vec3_copy(pos, cam->pos);
    cam->move_speed = speed;
    cam->mouse_sens = sens;
    cam->pitch = .0f;
    cam->yaw = -90.f;
    cam->zoom = 45.f;
    camera_update(cam);
}

void camera_process_keyboard(camera *cam, enum camera_move direction, float dt)
{
    float speed = cam->move_speed * dt;
    vec3 front;
    glm_vec3_scale(cam->front, speed, front);
    vec3 right;
    glm_vec3_scale(cam->right, speed, right);

    if (direction == CAMERA_MOVE_FORWARD)
        glm_vec3_add(cam->pos, front, cam->pos);
    if (direction == CAMERA_MOVE_BACKWARD)
        glm_vec3_sub(cam->pos, front, cam->pos);
    if (direction == CAMERA_MOVE_RIGHT)
        glm_vec3_add(cam->pos, right, cam->pos);
    if (direction == CAMERA_MOVE_LEFT)
        glm_vec3_sub(cam->pos, right, cam->pos);

    vec3 up = {0,0.1,0};
    if (direction == CAMERA_MOVE_UP)
        glm_vec3_add(cam->pos, up, cam->pos);
    if (direction == CAMERA_MOVE_DOWN)
        glm_vec3_sub(cam->pos, up, cam->pos);
}

void camera_process_mouse_move(camera *cam, float delta_x, float delta_y, boolean clamp)
{
    delta_x *= cam->mouse_sens;
    delta_y *= cam->mouse_sens;
    cam->yaw += delta_x;
    cam->pitch += delta_y;
    if (clamp)
        glm_clamp(cam->pitch, -85.f, 85.f);
    camera_update(cam);
}

void camera_process_mouse_scroll(camera *cam, float offset_y)
{
    cam->zoom -= offset_y;
    glm_clamp(cam->zoom, 1.f, 45.f);
}

void camera_view_mat(camera *cam, vec4 *dest)
{
    vec3 target; glm_vec3_add(cam->pos, cam->front, target);
    mat4 view; glm_lookat(cam->pos, target, cam->up, view);
    glm_mat4_copy(view, dest);
}

void camera_update(camera *cam)
{
    vec3 front = {
        cosf(glm_rad(cam->yaw)) * cosf(glm_rad(cam->pitch)),
        sin(glm_rad(cam->pitch)),
        sinf(glm_rad(cam->yaw)) * cosf(glm_rad(cam->pitch))};
    glm_normalize(front);
    glm_vec3_copy(front, cam->front);

    vec3 right; glm_cross(front, (vec3){0,1,0}, right);
    glm_normalize(right);
    glm_vec3_copy(right, cam->right);

    vec3 up; glm_cross(right, front, up);
    glm_normalize(up);
    glm_vec3_copy(up, cam->up);
}
