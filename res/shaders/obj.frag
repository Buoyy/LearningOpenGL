#version 330 core
#define NR_PT_LIGHTS 4

struct dir_light_t
{
    vec3 direction;
    vec3 ambient, diffuse, specular;
};

struct pt_light_t
{
    vec3 position, ambient, diffuse, specular;
    float att_const, att_linear, att_quadr;
};

/*struct spotlight_t
{
    vec3 position, direction;
    vec3 ambient, diffuse, specular;
    float cos_cutoff, cos_outer_cutoff;
    float att_const, att_linear, att_quadr;
};*/

struct material_t
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float     shininess;
};

vec3 calc_dir_light(dir_light_t light, vec3 norm, vec3 view_dir);
vec3 calc_pt_light(pt_light_t light, vec3 norm, vec3 Fpos, vec3 view_dir);
//vec3 calc_spotlight(spotlight_t light, vec3 norm, vec3 view_dir);

out vec4 fcolor; // Final color 

in vec3 Fpos, Fnorm;
in vec2 Fuv;

uniform vec3 view_pos;
uniform material_t material;
uniform dir_light_t dir_light;
uniform pt_light_t pt_lights[NR_PT_LIGHTS];

void main()
{
    vec3 norm = normalize(Fnorm);
    vec3 view_dir /*view posvec*/ = normalize(view_pos - Fpos);

    // Directional lighting 
    vec3 result = calc_dir_light(dir_light, norm, view_dir);

    // Point lights 
    for (int i = 0; i < NR_PT_LIGHTS; ++i)
        result += calc_pt_light(pt_lights[i], norm, Fpos, view_dir);

    fcolor = vec4(result, 1.0);
}

// ---------------------
// Function definitions 
// ---------------------
vec3 calc_dir_light(dir_light_t light, vec3 norm, vec3 view_dir)
{
    vec3 light_dir = normalize(-light.direction);

    // Ambient lighting 
    vec3 ambient = light.ambient * texture(material.diffuse, Fuv).rgb;

    // Diffuse lighting 
    float diff_amount = max(dot(light_dir, norm), 0.0);
    vec3 diffuse = light.diffuse * diff_amount * texture(material.diffuse, Fuv).rgb;

    // Specular lighting 
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec_amount = pow(max(dot(reflect_dir, view_dir), 0.0), material.shininess);
    vec3 specular = light.specular * spec_amount * texture(material.specular, Fuv).rgb;

    return (ambient + diffuse + specular);
}

vec3 calc_pt_light(pt_light_t light, vec3 norm, vec3 Fpos, vec3 view_dir)
{
    // Posvec of light 
    vec3 light_dir = normalize(light.position - Fpos);

    // Ambient lighting 
    vec3 ambient = light.ambient * texture(material.diffuse, Fuv).rgb;

    // Diffuse lighting 
    float diff_amount = max(dot(light_dir, norm), 0.0);
    vec3 diffuse = light.diffuse * diff_amount * texture(material.diffuse, Fuv).rgb;

    // Specular lighting 
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec_amount = pow(max(dot(reflect_dir, view_dir), 0.0), material.shininess);
    vec3 specular = light.specular * spec_amount * texture(material.specular, Fuv).rgb;

    // Attenuation 
    float dist = length(light.position - Fpos);
    float att = 1.0 / (light.att_const + light.att_linear * dist + light.att_quadr * (dist * dist));

    //ambient *= att;
    diffuse  *= att;
    specular *= att;

    return (ambient + diffuse + specular);
}



