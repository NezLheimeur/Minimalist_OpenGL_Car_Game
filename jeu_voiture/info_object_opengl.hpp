#ifndef INFO_OBJECT_OPENGL_HPP
#define INFO_OBJECT_OPENGL_HPP

#ifdef __APPLE__
#include <openGL/gl.h>		// Header File For The OpenGL32 Library
#include <openGL/glu.h>		// Header File For The GLu32 Library
#include <glut/glut.h>		// Header File For The GLut Library
#else
#include <GL/gl.h>
#endif



/** structure stockant les identifiants permettant l'affichage d'un objet 3D */
struct info_object_opengl
{
    GLuint vbo;  //identifiant du VBO de donnees
    GLuint vboi; //identifiant de VBO d'indices
    GLuint texture_id; //identificant de texture
    int nbr_triangle; //nombre de triangles de l'objet
};


#endif
