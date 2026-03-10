#version 330 core
out vec4 fcolor; // Final color 

in vec3 Fpos, Fnorm, Flight_pos;

uniform vec3 Ulight_color, Uobj_color;

void main()
{
    // Ambient lighting 
    float amb_strength = 0.14;
    vec3 ambient = amb_strength * Ulight_color;

    // Diffuse lighting: Calculate by dot product of 
    //light posvec wrt frag and the fragment's normal.
    vec3 norm = normalize(Fnorm);
    vec3 light_dir = normalize(Flight_pos - Fpos);
    float diff_amount = max(dot(light_dir, norm), 0.0);
    vec3 diffuse = diff_amount * Ulight_color;

    // Specular lighting: Calculate by dot product of 
    // Viewing posvec wrt frag (i.e. cam location,
    // origin in view space) and reflected ray.
    float spec_strength = 0.5;
    vec3 view_dir = normalize(/*origin*/ - Fpos);
    vec3 reflect_dir = reflect(-light_dir, norm); // minus because it is a posvec initially 
    float spec_amount = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = spec_strength * spec_amount * Ulight_color;

    // Finally, apply result of Phong lighting.
    vec3 phong = (ambient + diffuse + specular) * Uobj_color;
    fcolor = vec4(phong, 1.0); 
}
