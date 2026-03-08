#include "engine/camera.h"
#include "util/types.h"

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
    cam->m_forward = false;
    cam->m_backward = false;
    cam->m_left = false;
    cam->m_right = false;
    cam->m_up = false;
    cam->m_down = false;
    camera_update(cam);
}

void camera_move(camera *cam, float dt)
{
    float speed = cam->move_speed * dt;
    vec3 front;
    glm_vec3_scale(cam->front, speed, front);
    vec3 right;
    glm_vec3_scale(cam->right, speed, right);
    vec3 up = {0,1,0};
    glm_vec3_scale(up, speed * 0.5, up);
    vec3 zero; glm_vec3_zero(zero);

    if (cam->m_forward)
        glm_vec3_addadd(zero, front, cam->pos);
    else if (cam->m_backward)
        glm_vec3_addsub(zero, front, cam->pos);
    if (cam->m_right)
        glm_vec3_addadd(zero, right, cam->pos);
    else if (cam->m_left)
        glm_vec3_addsub(zero, right, cam->pos);
    if (cam->m_up)
        glm_vec3_addadd(zero, up, cam->pos);
    else if (cam->m_down)
        glm_vec3_addsub(zero, up, cam->pos);

}

void camera_process_keyboard(camera *cam, enum camera_move direction)
{
    if (direction == CAMERA_MOVE_FORWARD)
        cam->m_forward = !cam->m_forward;
    if (direction == CAMERA_MOVE_BACKWARD)
        cam->m_backward = !cam->m_backward;
    if (direction == CAMERA_MOVE_RIGHT)
        cam->m_right = !cam->m_right;
    if (direction == CAMERA_MOVE_LEFT)
        cam->m_left = !cam->m_left;
    if (direction == CAMERA_MOVE_UP)
        cam->m_up = !cam->m_up;
    if (direction == CAMERA_MOVE_DOWN)
        cam->m_down = !cam->m_down;
}

void camera_process_mouse_move(camera *cam, float delta_x, float delta_y, boolean clamp)
{
    delta_x *= cam->mouse_sens;
    delta_y *= cam->mouse_sens;
    cam->yaw += delta_x;
    cam->pitch += delta_y;
    if (clamp)
        cam->pitch = glm_clamp(cam->pitch, -85.f, 85.f);
    camera_update(cam);
}

void camera_process_mouse_scroll(camera *cam, float offset_y)
{
    cam->zoom -= offset_y;
    cam->zoom = glm_clamp(cam->zoom, 1.f, 45.f);
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
