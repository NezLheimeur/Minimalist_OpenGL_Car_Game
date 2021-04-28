#version 120

uniform vec4 translation;
uniform mat4 rotation;
uniform mat4 projection;

varying vec3 coordonnee_3d;
varying vec3 coordonnee_3d_locale;
varying vec3 normale;
varying vec4 color;

//Un Vertex Shader minimaliste
void main (void)
{
    //Les coordonnees 3D du sommet
    coordonnee_3d=gl_Vertex.xyz;

    //Coordonnees du sommet
    vec4 p=rotation*gl_Vertex+translation;
    coordonnee_3d_locale=p.xyz;

    //Projection du sommet
    p=projection*p;

    //Gestion des normales
    vec4 n=rotation*vec4(gl_Normal,1.0);
    normale=n.xyz;

    //Couleur du sommet
    color=gl_Color;

    //position dans l'espace ecran
    gl_Position = p;

    //coordonnees de textures
    gl_TexCoord[0]=gl_MultiTexCoord0;
}
