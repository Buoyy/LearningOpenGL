#ifndef E_CAMERA_H
#define E_CAMERA_H

#include "util/types.h"

#include <cglm/cglm.h>

enum camera_move 
{
    CAMERA_MOVE_FORWARD,
    CAMERA_MOVE_BACKWARD, 
    CAMERA_MOVE_LEFT, 
    CAMERA_MOVE_RIGHT,
    CAMERA_MOVE_UP,
    CAMERA_MOVE_DOWN
};

typedef struct 
{
    vec3 pos, front, up, right;
    float yaw, pitch;
    float move_speed, mouse_sens, zoom;
    boolean m_forward, m_backward, m_left, m_right, m_up, m_down;
} camera;

void camera_create(camera *cam, vec3 pos, float speed, float sens);
void camera_view_mat(camera *cam, mat4 dest);
void camera_move(camera *cam, float dt);
void camera_process_keyboard(camera *cam, enum camera_move direction);
void camera_process_mouse_move(camera *cam, float delta_x, float delta_y, boolean clamp);
void camera_process_mouse_scroll(camera *cam, float offset_y);
void camera_update(camera *cam);

#endif
