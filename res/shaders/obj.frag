#version 330 core
struct light_t
{
    vec3 pos;
    vec3 ambient, diffuse, specular;
};
struct material_t
{
    vec3 ambient, diffuse, specular;
    float shininess;
};

out vec4 fcolor; // Final color 

in vec3 Fpos, Fnorm;

uniform vec3 view_pos;
uniform material_t material;
uniform light_t light;

void main()
{
    // Ambient lighting 
    vec3 ambient = light.ambient * material.ambient;

    // Diffuse lighting: Calculate by dot product of 
    //light posvec wrt frag and the fragment's normal.
    vec3 norm = normalize(Fnorm);
    vec3 light_dir = normalize(light.pos - Fpos);
    float diff_amount = max(dot(light_dir, norm), 0.0);
    vec3 diffuse = diff_amount * (material.diffuse * light.diffuse);

    // Specular lighting: Calculate by dot product of 
    // Viewing posvec wrt frag and reflected ray.
    vec3 view_dir = normalize(view_pos - Fpos);
    vec3 reflect_dir = reflect(-light_dir, norm); // minus because it is a posvec initially 
    float spec_amount = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular = spec_amount * (material.specular * light.specular);

    // Finally, apply result of Phong lighting.
    vec3 phong = (ambient + diffuse + specular);
    fcolor = vec4(phong, 1.0); 
}
