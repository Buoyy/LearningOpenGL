#version 330 core

out vec4 fragcolor;
in vec3 color;
in vec2 uv;

uniform float mix_amount;
uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
    fragcolor = mix(texture(tex1, uv), texture(tex2, vec2(-uv.x, uv.y)), mix_amount);
}
