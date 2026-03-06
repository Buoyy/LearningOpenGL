#version 330 core

layout (location = 0) in vec2 _pos;
layout (location = 1) in vec3 _color;
layout (location = 2) in vec2 _uv;

out vec2 uv;
out vec3 color;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(_pos, 0.0, 1.0);
    color = _color;
    uv = _uv;
}
