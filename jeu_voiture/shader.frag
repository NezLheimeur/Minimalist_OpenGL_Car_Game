#version 120

uniform vec4 translation;
uniform mat4 rotation;

varying vec3 coordonnee_3d;
varying vec3 coordonnee_3d_locale;
varying vec3 normale;
varying vec4 color;

uniform sampler2D texture;

uniform vec2 texture_translation;

vec3 light=vec3(0.0,5.0,-5.0);

//Un Fragment Shader minimaliste
void main (void)
{
    vec3 n=normalize(normale);
    vec3 d=normalize(light-coordonnee_3d_locale);
    vec3 r=reflect(d,n);
    vec3 o=normalize(-coordonnee_3d_locale);

    float diffuse=0.8*clamp(dot(n,d),0.0,1.0);
    float specular=0.2*pow(clamp(dot(r,o),0.0,1.0),128.0);
    float ambiant=0.4;

    vec4 white=vec4(1.0,1.0,1.0,0.0);

    vec2 tex_coord=gl_TexCoord[0].xy+texture_translation;
    vec4 color_texture=texture2D(texture,tex_coord);
    vec4 color_final=color*color_texture;

    gl_FragColor = (ambiant+diffuse)*color_final+specular*white;

}
