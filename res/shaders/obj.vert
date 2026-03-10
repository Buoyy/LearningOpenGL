#version 330 core
layout (location = 0) in vec3 Vpos;
layout (location = 1) in vec3 Vnorm;

uniform mat4 model, view, proj;
uniform vec3 Ulight_pos;

out vec3 Fpos, Fnorm, Flight_pos;

void main()
{
    gl_Position = proj * view * model * vec4(Vpos, 1.0);
    Fpos = vec3(view * model * vec4(Vpos, 1.0));
    mat4 norm_mat = transpose(inverse(view * model));
    Fnorm = vec3(norm_mat * vec4(Fpos, 1.0));
    Flight_pos = vec3(view * model * vec4(Ulight_pos, 1.0));
}
