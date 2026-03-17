#version 330 core

out vec4 fragcolor;
in vec2 uv;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    fragcolor = mix(texture(tex1, uv), texture(tex2, uv), 0.25);
}
