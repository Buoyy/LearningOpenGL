#version 330 core
layout (location = 0) in vec3 _pos;

uniform mat4 model, view, proj;

void main()
{
    gl_Position = proj * view * model * vec4(_pos, 1.0);
}
