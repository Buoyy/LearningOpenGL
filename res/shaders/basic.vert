#version 330 core

layout (location = 0) in vec2 _pos;
layout (location = 1) in vec3 _color;
layout (location = 2) in vec2 _uv;

out vec2 uv;
out vec3 color;

void main()
{
    gl_Position = vec4(_pos.x, _pos.y, 0.0, 1.0);
    color = _color;
    uv = _uv;
}
