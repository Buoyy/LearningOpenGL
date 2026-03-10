#version 330 core
struct light_t
{
    vec3 pos;
    vec3 ambient, diffuse, specular;
};
struct material_t
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float     shininess;
};

out vec4 fcolor; // Final color 

in vec3 Fpos, Fnorm;
in vec2 Fuv;

uniform vec3 view_pos;
uniform material_t material;
uniform light_t light;
uniform float time;

void main()
{
    // Ambient lighting 
    vec3 ambient = light.ambient * texture(material.diffuse, Fuv).rgb;

    // Diffuse lighting: Calculate by dot product of 
    //light posvec wrt frag and the fragment's normal.
    vec3 norm = normalize(Fnorm);
    vec3 light_dir = normalize(light.pos - Fpos);
    float diff_amount = max(dot(light_dir, norm), 0.0);
    vec3 diffuse = diff_amount * light.diffuse * 
        texture(material.diffuse, Fuv).rgb;

    // Specular lighting: Calculate by dot product of 
    // Viewing posvec wrt frag and reflected ray.
    vec3 view_dir = normalize(view_pos - Fpos);
    vec3 reflect_dir = reflect(-light_dir, norm); // minus because it is a posvec initially 
    float spec_amount = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular = texture(material.specular, Fuv).rgb * spec_amount * light.specular;

    // Emission mapping 
    vec3 emission = vec3(0.0);
    if (texture(material.specular, Fuv).r == 0)
    {
        emission = texture(material.emission, Fuv+vec2(0.0, time/2)).rgb;
        emission = (sin(time)+1) *0.5 * emission;
    }

    // Finally, apply result of Phong lighting.
    vec3 phong = (ambient + diffuse + specular + emission);
    fcolor = vec4(phong, 1.0); 
}
