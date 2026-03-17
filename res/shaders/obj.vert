#version 330 core
layout (location = 0) in vec3 Vpos;
layout (location = 1) in vec3 Vnorm;
layout (location = 2) in vec2 Vuv;

out vec3 Fpos, Fnorm;
out vec2 Fuv;

uniform mat4 model, view, proj;

void main()
{
    Fpos = vec3(model * vec4(Vpos, 1.0));
    Fnorm = mat3(transpose(inverse(model))) * Vnorm;
    Fuv = Vuv;
    gl_Position = proj * view * model * vec4(Vpos, 1.0);
}
