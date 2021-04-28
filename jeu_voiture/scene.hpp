#ifndef SCENE_HPP
#define SCENE_HPP

#ifdef __APPLE__
#include <openGL/gl.h>		// Header File For The OpenGL32 Library
#include <openGL/glu.h>		// Header File For The GLu32 Library
#include <glut/glut.h>		// Header File For The GLut Library
#else
#include <GL/glu.h>
#endif

struct info_object_opengl;
struct mat4;
struct vec3;


void chargement_voiture(info_object_opengl* info_object,GLuint shader_id);
void chargement_route(info_object_opengl* info_object,GLuint shader_id);
void chargement_obstacle(info_object_opengl* info_object,GLuint shader_id);
void chargement_projectile(info_object_opengl* info_object,GLuint shader_id);
void chargement_objet_ciel(info_object_opengl* info_object,GLuint shader_id);
void chargement_herbe(info_object_opengl* info_object,GLuint shader_id);

#endif
