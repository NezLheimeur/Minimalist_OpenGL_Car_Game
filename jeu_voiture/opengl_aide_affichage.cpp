
#ifdef __APPLE__
#include <openGL/gl.h>		// Header File For The OpenGL32 Library
#include <openGL/glu.h>		// Header File For The GLu32 Library
#include <glut/glut.h>		// Header File For The GLut Library
#else
#include <GL/glew.h>
#endif

#include "opengl_aide_affichage.hpp"

#include "info_object_opengl.hpp"
#include "mat4.hpp"
#include "vec3.hpp"
#include "vec2.hpp"
#include "glutils.hpp"
#include "vertex_opengl.hpp"
#include "image.hpp"
#include "mesh.hpp"

#include <cstdlib>
#include <cassert>

void affiche_objet(info_object_opengl info_object,GLuint shader_id,mat4 rotation,vec3 translation)
{
    //selection du VBO courant
    glBindBuffer(GL_ARRAY_BUFFER,info_object.vbo); PRINT_OPENGL_ERROR();

    // mise en place des differents pointeurs
    glEnableClientState(GL_VERTEX_ARRAY); PRINT_OPENGL_ERROR();
    glVertexPointer(3, GL_FLOAT, sizeof(vertex_opengl), 0); PRINT_OPENGL_ERROR();

    glEnableClientState(GL_NORMAL_ARRAY); PRINT_OPENGL_ERROR();
    glNormalPointer(GL_FLOAT, sizeof(vertex_opengl), buffer_offset(sizeof(vec3))); PRINT_OPENGL_ERROR();

    glEnableClientState(GL_COLOR_ARRAY); PRINT_OPENGL_ERROR();
    glColorPointer(3,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(2*sizeof(vec3))); PRINT_OPENGL_ERROR();

    glEnableClientState(GL_TEXTURE_COORD_ARRAY); PRINT_OPENGL_ERROR();
    glTexCoordPointer(3,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(3*sizeof(vec3))); PRINT_OPENGL_ERROR();


    //mise en place des transformations
    glUniformMatrix4fv(get_uni_loc(shader_id,"rotation"),1,false,pointeur(rotation)); PRINT_OPENGL_ERROR();
    glUniform4f(get_uni_loc(shader_id,"translation"),translation.x,translation.y,translation.z,0.0f);PRINT_OPENGL_ERROR();

    //affichage
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,info_object.vboi); PRINT_OPENGL_ERROR();
    glBindTexture(GL_TEXTURE_2D, info_object.texture_id); PRINT_OPENGL_ERROR();
    glDrawElements(GL_TRIANGLES, 3*info_object.nbr_triangle, GL_UNSIGNED_INT, 0); PRINT_OPENGL_ERROR();


}

void charge_image(const std::string filename,info_object_opengl* info_object,GLuint shader_id)
{
    // Chargement d'une texture (seul les textures tga sont supportes)
    Image  *image = image_load_tga(filename);

    if (image) //verification que l'image est bien chargee
    {

        //Creation d'un identifiant pour la texture
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); PRINT_OPENGL_ERROR();
        glGenTextures(1, &info_object->texture_id); PRINT_OPENGL_ERROR();

        //Selection de la texture courante a partir de son identifiant
        glBindTexture(GL_TEXTURE_2D, info_object->texture_id); PRINT_OPENGL_ERROR();

        //Parametres de la texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); PRINT_OPENGL_ERROR();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); PRINT_OPENGL_ERROR();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); PRINT_OPENGL_ERROR();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); PRINT_OPENGL_ERROR();

        //Envoie de l'image en memoire video
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data); PRINT_OPENGL_ERROR();

        delete image;
    }
    else
    {
        std::cerr<<"Erreur chargement de l'image, etes-vous dans le bon repertoire?"<<std::endl;
        abort();
    }

    glUniform1i (get_uni_loc(shader_id, "texture"), 0); PRINT_OPENGL_ERROR();

}

void charge_maillage_vbo(info_object_opengl* info_object,const mesh& m)
{
    assert(m.vertex.size()>0);
    assert(m.connectivity.size()>0);

    //buffer de donnees
    glGenBuffers(1,&info_object->vbo); PRINT_OPENGL_ERROR();
    glBindBuffer(GL_ARRAY_BUFFER,info_object->vbo); PRINT_OPENGL_ERROR();
    glBufferData(GL_ARRAY_BUFFER,m.vertex.size()*sizeof(vertex_opengl),&m.vertex[0],GL_STATIC_DRAW); PRINT_OPENGL_ERROR();

    //buffer d'indice
    glGenBuffers(1,&info_object->vboi); PRINT_OPENGL_ERROR();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,info_object->vboi); PRINT_OPENGL_ERROR();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,m.connectivity.size()*sizeof(triangle_index),&m.connectivity[0],GL_STATIC_DRAW); PRINT_OPENGL_ERROR();

    info_object->nbr_triangle=m.connectivity.size();
}


