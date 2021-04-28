#ifdef __APPLE__
#include <openGL/gl.h>		// Header File For The OpenGL32 Library
#include <openGL/glu.h>		// Header File For The GLu32 Library
#include <glut/glut.h>		// Header File For The GLut Library
#else
#include <GL/glew.h>
#endif

#include "scene.hpp"

#include "info_object_opengl.hpp"
#include "vec3.hpp"
#include "vec2.hpp"
#include "mat4.hpp"
#include "vertex_opengl.hpp"
#include "triangle_index.hpp"
#include "image.hpp"
#include "mesh.hpp"
#include "opengl_aide_affichage.hpp"
#include "glutils.hpp"

#include <cassert>
#include <cmath>




void chargement_voiture(info_object_opengl* info_object,GLuint shader_id)
{
    assert(info_object!=NULL);
    //Coordonnees des sommets
    vec3 p0=vec3(0.0f,0.0f,0.0f);
    vec3 p1=vec3(0.05f,0.12f,0.0f);
    vec3 p2=vec3(0.35f,0.15f,0.0f);
    vec3 p3=vec3(0.45f,0.22f,0.0f);
    vec3 p4=vec3(0.71f,0.22f,0.0f);
    vec3 p5=vec3(0.81f,0.17f,0.0f);
    vec3 p6=vec3(0.95f,0.16f,0.0f);
    vec3 p7=vec3(1.0f,0.0f,0.0f);
    vec3 p8=vec3(0.81f,0.0f,0.0f);
    vec3 p9=vec3(0.71f,0.0f,0.0f);
    vec3 p10=vec3(0.45f,0.0f,0.0f);
    vec3 p11=vec3(0.35f,0.0f,0.0f);
    
    vec3 p12=vec3(0.0f,0.0f,0.35f);
    vec3 p13=vec3(0.05f,0.12f,0.35f);
    vec3 p14=vec3(0.35f,0.15f,0.35f);
    vec3 p15=vec3(0.45f,0.22f,0.35f);
    vec3 p16=vec3(0.71f,0.22f,0.35f);
    vec3 p17=vec3(0.81f,0.17f,0.35f);
    vec3 p18=vec3(0.95f,0.16f,0.35f);
    vec3 p19=vec3(1.0f,0.0f,0.35f);
    vec3 p20=vec3(0.81f,0.0f,0.35f);
    vec3 p21=vec3(0.71f,0.0f,0.35f);
    vec3 p22=vec3(0.45f,0.0f,0.35f);
    vec3 p23=vec3(0.35f,0.0f,0.35f);
    
    //normales pour chaque sommet
    vec3 n0=vec3(1.0f,0.0f,-1.0f);
    vec3 n1=vec3(1.0f,0.0f,-1.0f);
    vec3 n2=vec3(-1.0f,1.0f,0.0f);
    vec3 n3=vec3(1.0f,-1.0f,0.0f);
    
    vec3 n4=vec3(-1.0f,-1.0f,0.0f);
    vec3 n5=vec3(1.0f,1.0f,0.0f);
    vec3 n6=vec3(-1.0f,-1.0f,-1.0f);
    vec3 n7=vec3(-1.0f,1.0f,-1.0f);
    
    vec3 n8=vec3(0.0f,0.0f,0.0f);
    vec3 n9=vec3(0.0f,0.0f,0.0f);
    vec3 n10=vec3(0.0f,0.0f,0.0f);
    vec3 n11=vec3(0.0f,0.0f,0.0f);
    
    vec3 n12=vec3(1.0f,0.0f,1.0f);
    vec3 n13=vec3(1.0f,0.0f,1.0f);
    vec3 n14=vec3(-1.0f,1.0f,0.0f);
    vec3 n15=vec3(1.0f,-1.0f,0.0f);
    
    vec3 n16=vec3(-1.0f,-1.0f,0.0f);
    vec3 n17=vec3(1.0f,1.0f,0.0f);
    vec3 n18=vec3(-1.0f,-1.0f,1.0f);
    vec3 n19=vec3(-1.0f,1.0f,1.0f);
    
    vec3 n20=vec3(0.0f,0.0f,0.0f);
    vec3 n21=vec3(0.0f,0.0f,0.0f);
    vec3 n22=vec3(0.0f,0.0f,0.0f);
    vec3 n23=vec3(0.0f,0.0f,0.0f);
    
    //couleur pour chaque sommet
    vec3 c0=vec3(1.0f,1.0f,1.0f);
    
    //textures des sommets
    vec2 t0=vec2(0.15f,0.81f);
    vec2 t1=vec2(0.18f,0.72f);
    vec2 t2=vec2(0.40f,0.69f);
    vec2 t3=vec2(0.46f,0.64f);
    vec2 t4=vec2(0.63f,0.64f);
    vec2 t5=vec2(0.71f,0.68f);
    vec2 t6=vec2(0.81f,0.69f);
    vec2 t7=vec2(0.85f,0.81f);
    vec2 t8=vec2(0.71f,0.81f);
    vec2 t9=vec2(0.63f,0.81f);
    vec2 t10=vec2(0.46f,0.81f);
    vec2 t11=vec2(0.40f,0.81f);
    vec2 t12=vec2(0.15f,0.29f);
    vec2 t13=vec2(0.18f,0.38f);
    vec2 t14=vec2(0.40f,0.41f);
    vec2 t15=vec2(0.46f,0.46f);
    vec2 t16=vec2(0.63f,0.46f);
    vec2 t17=vec2(0.71f,0.42f);
    vec2 t18=vec2(0.81f,0.41f);
    vec2 t19=vec2(0.85f,0.29f);
    vec2 t20=vec2(0.71f,0.29f);
    vec2 t21=vec2(0.63f,0.29f);
    vec2 t22=vec2(0.46f,0.29f);
    vec2 t23=vec2(0.40f,0.29f);
    
    vertex_opengl v0=vertex_opengl(p0,n0,c0,t0);
    vertex_opengl v1=vertex_opengl(p1,n1,c0,t1);
    vertex_opengl v2=vertex_opengl(p2,n2,c0,t2);
    vertex_opengl v3=vertex_opengl(p3,n3,c0,t3);
    vertex_opengl v4=vertex_opengl(p4,n4,c0,t4);
    vertex_opengl v5=vertex_opengl(p5,n5,c0,t5);
    vertex_opengl v6=vertex_opengl(p6,n6,c0,t6);
    vertex_opengl v7=vertex_opengl(p7,n7,c0,t7);
    vertex_opengl v8=vertex_opengl(p8,n8,c0,t8);
    vertex_opengl v9=vertex_opengl(p9,n9,c0,t9);
    vertex_opengl v10=vertex_opengl(p10,n10,c0,t10);
    vertex_opengl v11=vertex_opengl(p11,n11,c0,t11);
    vertex_opengl v12=vertex_opengl(p12,n12,c0,t12);
    vertex_opengl v13=vertex_opengl(p13,n13,c0,t13);
    vertex_opengl v14=vertex_opengl(p14,n14,c0,t14);
    vertex_opengl v15=vertex_opengl(p15,n15,c0,t15);
    vertex_opengl v16=vertex_opengl(p16,n16,c0,t16);
    vertex_opengl v17=vertex_opengl(p17,n17,c0,t17);
    vertex_opengl v18=vertex_opengl(p18,n18,c0,t18);
    vertex_opengl v19=vertex_opengl(p19,n19,c0,t19);
    vertex_opengl v20=vertex_opengl(p20,n20,c0,t20);
    vertex_opengl v21=vertex_opengl(p21,n21,c0,t21);
    vertex_opengl v22=vertex_opengl(p22,n22,c0,t22);
    vertex_opengl v23=vertex_opengl(p23,n23,c0,t23);
    
    //tableau entrelacant coordonnees-normales
    vertex_opengl geometrie[]={v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,
        v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23};
    
    
    //indices des triangles
    triangle_index tri0=triangle_index(0,1,2);    //face avant
    triangle_index tri1=triangle_index(0,2,11);
    triangle_index tri2=triangle_index(2,3,11);
    triangle_index tri3=triangle_index(3,10,11);
    triangle_index tri4=triangle_index(3,4,10);
    triangle_index tri5=triangle_index(4,9,10);
    triangle_index tri6=triangle_index(4,5,9);
    triangle_index tri7=triangle_index(5,8,9);
    triangle_index tri8=triangle_index(5,6,8);
    triangle_index tri9=triangle_index(6,7,8);
    
    triangle_index tri10=triangle_index(0,1,13);   //face du dessus
    triangle_index tri11=triangle_index(0,12,13);
    triangle_index tri12=triangle_index(1,13,14);
    triangle_index tri13=triangle_index(1,2,14);
    triangle_index tri14=triangle_index(2,14,15);
    triangle_index tri15=triangle_index(2,3,15);
    triangle_index tri16=triangle_index(3,4,16);
    triangle_index tri17=triangle_index(3,15,16);
    triangle_index tri18=triangle_index(4,16,17);
    triangle_index tri19=triangle_index(4,5,17);
    triangle_index tri20=triangle_index(5,17,18);
    triangle_index tri21=triangle_index(5,6,18);
    triangle_index tri22=triangle_index(7,6,18);
    triangle_index tri23=triangle_index(6,7,19);
    
    triangle_index tri24=triangle_index(0,7,19);  //face du dessous
    triangle_index tri25=triangle_index(0,12,19);
    
    triangle_index tri26=triangle_index(12,13,14);    //face arriere
    triangle_index tri27=triangle_index(12,14,23);
    triangle_index tri28=triangle_index(14,15,23);
    triangle_index tri29=triangle_index(15,22,23);
    triangle_index tri30=triangle_index(15,16,22);
    triangle_index tri31=triangle_index(16,21,22);
    triangle_index tri32=triangle_index(16,17,21);
    triangle_index tri33=triangle_index(17,20,21);
    triangle_index tri34=triangle_index(18,6,19);
    triangle_index tri35=triangle_index(7,19,6);
    triangle_index tri36=triangle_index(17,18,19);
    triangle_index tri37=triangle_index(17,19,20);
    
    triangle_index index[]={tri0,tri1,tri2,tri3,tri4,tri5,tri6,tri7,tri8,tri9,tri10,tri11,tri12,tri13,tri14,tri15,
        tri16,tri17,tri18,tri19,tri20,tri21,tri22,tri23,tri24,tri25,tri26,tri27,tri28,tri29,
        tri30,tri31,tri32,tri33,tri34,tri35,tri36,tri37};
    

    info_object->nbr_triangle=38;


    //attribution d'un buffer de donnees (1 indique la création d'un buffer)
    glGenBuffers(1,&info_object->vbo); PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,info_object->vbo); PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,sizeof(geometrie),geometrie,GL_STATIC_DRAW); PRINT_OPENGL_ERROR();



    //attribution d'un autre buffer d'indice
    glGenBuffers(1,&info_object->vboi); PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,info_object->vboi); PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW); PRINT_OPENGL_ERROR();


    charge_image("car.tga",info_object,shader_id);

}


void chargement_route(info_object_opengl* info_object,GLuint shader_id)
{
    assert(info_object!=NULL);

    //coordonnees geometriques des sommets
    vec3 p0=vec3(-2.0f,-0.5f,-100.0f);
    vec3 p1=vec3(-2.0f,-0.5f,+100.0f);
    vec3 p2=vec3(+2.0f,-0.5f,+100.0f);
    vec3 p3=vec3(+2.0f,-0.5f,-100.0f);
    
    //normales pour chaque sommet
    vec3 n0=vec3(0.0f,1.0f,0.0f);
    vec3 n1=vec3(0.0f,1.0f,0.0f);
    vec3 n2=vec3(0.0f,1.0f,0.0f);
    vec3 n3=vec3(0.0f,1.0f,0.0f);
    
    //couleur pour chaque sommet
    vec3 c0=vec3(1.0f,1.0f,1.0f);
    vec3 c1=vec3(1.0f,1.0f,1.0f);
    vec3 c2=vec3(1.0f,1.0f,1.0f);
    vec3 c3=vec3(1.0f,1.0f,1.0f);
    
    //texture du sommet
    vec2 t3=vec2(0.0f,0.0f);
    vec2 t0=vec2(1.0f,0.0f);
    vec2 t1=vec2(1.0f,1.0f);
    vec2 t2=vec2(0.0f,1.0f);
    
    
    
    vertex_opengl v0=vertex_opengl(p0,n0,c0,t0);
    vertex_opengl v1=vertex_opengl(p1,n1,c1,t1);
    vertex_opengl v2=vertex_opengl(p2,n2,c2,t2);
    vertex_opengl v3=vertex_opengl(p3,n3,c3,t3);
    
    
    //tableau entrelacant coordonnees-normales
    vertex_opengl geometrie[]={v0,v1,v2,v3};
    
    
    //indice des triangles
    triangle_index tri0=triangle_index(0,1,2);
    triangle_index tri1=triangle_index(0,2,3);
    triangle_index index[]={tri0,tri1};
    
    info_object->nbr_triangle=2;


    //attribution d'un buffer de donnees (1 indique la création d'un buffer)
    glGenBuffers(1,&info_object->vbo); PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,info_object->vbo); PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,sizeof(geometrie),geometrie,GL_STATIC_DRAW); PRINT_OPENGL_ERROR();



    //attribution d'un autre buffer de donnees
    glGenBuffers(1,&info_object->vboi); PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,info_object->vboi); PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW); PRINT_OPENGL_ERROR();


    charge_image("route_droite_petite.tga",info_object,shader_id);
    
}

void chargement_herbe(info_object_opengl* info_object,GLuint shader_id)
{
    assert(info_object!=NULL);
    
    //coordonnees geometriques des sommets
    vec3 p0=vec3(-2.0f,-0.5f,-100.0f);
    vec3 p1=vec3(-2.0f,-0.5f,+100.0f);
    vec3 p2=vec3(-20.0f,-0.5f,+100.0f);
    vec3 p3=vec3(-20.0f,-0.5f,-100.0f);
    
    //normales pour chaque sommet
    vec3 n0=vec3(0.0f,1.0f,0.0f);
    
    //couleur pour chaque sommet
    vec3 c0=vec3(1.0f,1.0f,1.0f);
    
    //texture du sommet
    vec2 t0=vec2(1.0f,0.0f);
    vec2 t1=vec2(1.0f,1.0f);
    vec2 t2=vec2(0.0f,1.0f);
    vec2 t3=vec2(0.0f,0.0f);
    
    vertex_opengl v0=vertex_opengl(p0,n0,c0,t0);
    vertex_opengl v1=vertex_opengl(p1,n0,c0,t1);
    vertex_opengl v2=vertex_opengl(p2,n0,c0,t2);
    vertex_opengl v3=vertex_opengl(p3,n0,c0,t3);
    
    
    //tableau entrelacant coordonnees-normales
    vertex_opengl geometrie[]={v0,v1,v2,v3};
    
    
    //indice des triangles
    triangle_index tri0=triangle_index(0,1,2);
    triangle_index tri1=triangle_index(0,2,3);
    triangle_index index[]={tri0,tri1};
    
    info_object->nbr_triangle=2;
    
    
    //attribution d'un buffer de donnees (1 indique la création d'un buffer)
    glGenBuffers(1,&info_object->vbo); PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,info_object->vbo); PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,sizeof(geometrie),geometrie,GL_STATIC_DRAW); PRINT_OPENGL_ERROR();
    
    
    
    //attribution d'un autre buffer de donnees
    glGenBuffers(1,&info_object->vboi); PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,info_object->vboi); PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW); PRINT_OPENGL_ERROR();
    
    
    charge_image("grass.tga",info_object,shader_id);
}


void chargement_objet_ciel(info_object_opengl* info_object,GLuint shader_id)
{
    //coordonnees geometriques des sommets
    vec3 p0=vec3(-48.0f,-48.0f,100.0f);
    vec3 p1=vec3(48.0f,-48.0f,100.0f);
    vec3 p2=vec3(-48.0f,48.0f,100.0f);
    vec3 p3=vec3(48.0f,48.0f,100.0f);
    
    //normales pour chaque sommet
    vec3 n0=vec3(0.0f,0.0f,-1.0f);
    
    //couleur pour chaque sommet
    vec3 c0=vec3(1.0f,1.0f,1.0f);

    
    //texture du sommet
    vec2 t2=vec2(0.0f,0.0f);
    vec2 t3=vec2(1.0f,0.0f);
    vec2 t0=vec2(0.0f,1.0f);
    vec2 t1=vec2(1.0f,1.0f);
    
    vertex_opengl v0=vertex_opengl(p0,n0,c0,t0);
    vertex_opengl v1=vertex_opengl(p1,n0,c0,t1);
    vertex_opengl v2=vertex_opengl(p2,n0,c0,t2);
    vertex_opengl v3=vertex_opengl(p3,n0,c0,t3);
    
    
    //tableau entrelacant coordonnees-normales
    vertex_opengl geometrie[]={v0,v1,v2,v3};
    
    
    //indice des triangles
    triangle_index tri0=triangle_index(0,1,2);
    triangle_index tri1=triangle_index(1,2,3);
    triangle_index index[]={tri0,tri1};
    
    info_object->nbr_triangle=2;
    
    //attribution d'un buffer de donnees (1 indique la crÃ©ation d'un buffer)
    glGenBuffers(1,&info_object->vbo); PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,info_object->vbo); PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,sizeof(geometrie),geometrie,GL_STATIC_DRAW); PRINT_OPENGL_ERROR();
    
    
    
    //attribution d'un autre buffer de donnees
    glGenBuffers(1,&info_object->vboi); PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,info_object->vboi); PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW); PRINT_OPENGL_ERROR();
    
    
    charge_image("ciel2.tga",info_object,shader_id);
}

void chargement_obstacle(info_object_opengl* info_object,GLuint shader_id)
{
        assert(info_object!=NULL);
        
        //coordonnees geometriques des sommets
        vec3 p0=vec3(0.0f,-0.3f,0.0f);
        vec3 p1=vec3(0.4f,-0.3f,0.0f);
        vec3 p2=vec3(0.0f,0.1f,0.0f);
        vec3 p3=vec3(0.4f,0.1f,0.0f);
        
        
        vec3 p4=vec3(0.0f,-0.3f,1.0f);
        vec3 p5=vec3(0.4f,-0.3f,1.0f);
        vec3 p6=vec3(0.0f,0.1f,1.0f);
        vec3 p7=vec3(0.4f,0.1f,1.0f);
        
        
        
        //normales pour chaque sommet
        vec3 n0=vec3(0.0f,1.0f,0.0f);
    
        
        //couleur pour chaque sommet
        vec3 c0=vec3(1.0f,1.0f,1.0f);
    
        
        
        //texture du sommet
        vec2 t0=vec2(0.0f,0.0f);
        vec2 t1=vec2(1.0f,0.0f);
        vec2 t2=vec2(0.0f,1.0f);
        vec2 t3=vec2(1.0f,1.0f);
        vec2 t4=vec2(0.0f,0.0f);
        vec2 t5=vec2(1.0f,0.0f);
        vec2 t6=vec2(0.0f,1.0f);
        vec2 t7=vec2(1.0f,1.0f);
        
        vertex_opengl v0=vertex_opengl(p0,n0,c0,t0);
        vertex_opengl v1=vertex_opengl(p1,n0,c0,t1);
        vertex_opengl v2=vertex_opengl(p2,n0,c0,t2);
        vertex_opengl v3=vertex_opengl(p3,n0,c0,t3);
        vertex_opengl v4=vertex_opengl(p4,n0,c0,t4);
        vertex_opengl v5=vertex_opengl(p5,n0,c0,t5);
        vertex_opengl v6=vertex_opengl(p6,n0,c0,t6);
        vertex_opengl v7=vertex_opengl(p7,n0,c0,t7);
    
        //tableau entrelacant coordonnees-normales
        vertex_opengl geometrie[]={v0,v1,v2,v3,v4,v5,v6,v7};
        
        
        //indice des triangles
        
        triangle_index tri0=triangle_index(0,1,2);
        triangle_index tri1=triangle_index(1,3,2);
        //face parallèle
        triangle_index tri2=triangle_index(4,5,6);
        triangle_index tri3=triangle_index(5,6,7);
    
        
        
        //face de droite
        triangle_index tri4=triangle_index(1,5,3);
        triangle_index tri5=triangle_index(5,3,7);
        
        // face de gauche
        triangle_index tri6=triangle_index(2,4,6);
        triangle_index tri7=triangle_index(0,4,2);
        // dessus
        triangle_index tri8=triangle_index(3,2,6);
        triangle_index tri9=triangle_index(3,7,6);
        
        // en dessous
        triangle_index tri10=triangle_index(0,1,4);
        triangle_index tri11=triangle_index(1,4,5);
        
        
        
        triangle_index index[]={tri0, tri1, tri2, tri3, tri4, tri5, tri6, tri7, tri8, tri9, tri10, tri11};
        
        info_object->nbr_triangle=2*6;
        
        
        //attribution d'un buffer de donnees (1 indique la crÃ©ation d'un buffer)
        glGenBuffers(1,&info_object->vbo); PRINT_OPENGL_ERROR();
        //affectation du buffer courant
        glBindBuffer(GL_ARRAY_BUFFER,info_object->vbo); PRINT_OPENGL_ERROR();
        //copie des donnees des sommets sur la carte graphique
        glBufferData(GL_ARRAY_BUFFER,sizeof(geometrie),geometrie,GL_STATIC_DRAW); PRINT_OPENGL_ERROR();
        
        
        
        //attribution d'un autre buffer d'indice
        glGenBuffers(1,&info_object->vboi); PRINT_OPENGL_ERROR();
        //affectation du buffer courant (buffer d'indice)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,info_object->vboi); PRINT_OPENGL_ERROR();
        //copie des indices sur la carte graphique
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW); PRINT_OPENGL_ERROR();
        
        
        charge_image("explosive.tga",info_object,shader_id);
        
    
}

void chargement_projectile(info_object_opengl* info_object,GLuint shader_id)
{
    assert(info_object!=NULL);
    
    //mise en place des positions
    vec3 p0=vec3(0.0f,0.05f,0.2f);
    vec3 p1=vec3(0.1,0.05,0.2);
    vec3 p2=vec3(0.1,0.15,0.2);
    vec3 p3=vec3(0.0,0.15,0.2);
    vec3 p4=vec3(0.0,0.15,0.3);
    vec3 p5=vec3(0.1,0.15,0.3);
    vec3 p6=vec3(0.1,0.05,0.3);
    vec3 p7=vec3(0.0,0.05,0.3);
    
    
    
    //mise en place des normales
    vec3 n0=vec3(0,1,0);
    
    //mise en place des couleurs
    vec3 c0=vec3(1,1.0,1.0);
    
    //mise en place des textures
    vec2 t0=vec2(0.15,0.81);
    vec2 t1=vec2(0.18,0.72);
    vec2 t2=vec2(0.4,0.69);
    vec2 t3=vec2(0.46,0.64);
    vec2 t4=vec2(0.63,0.64);
    vec2 t5=vec2(0.71,0.68);
    vec2 t6=vec2(0.82,0.69);
    vec2 t7=vec2(0.85,0.81);
    
    
    vertex_opengl v0=vertex_opengl(p0,n0,c0,t0);
    vertex_opengl v1=vertex_opengl(p1,n0,c0,t1);
    vertex_opengl v2=vertex_opengl(p2,n0,c0,t2);
    vertex_opengl v3=vertex_opengl(p3,n0,c0,t3);
    vertex_opengl v4=vertex_opengl(p4,n0,c0,t4);
    vertex_opengl v5=vertex_opengl(p5,n0,c0,t5);
    vertex_opengl v6=vertex_opengl(p6,n0,c0,t6);
    vertex_opengl v7=vertex_opengl(p7,n0,c0,t7);
    
    
    //tableau entrelacant coordonnees-normales
    vertex_opengl geometrie[]={v0,v1,v2,v3,v4,v5,v6,v7};
    
    //indice des triangles
    
    triangle_index tri0=triangle_index(0,1,2);
    triangle_index tri1=triangle_index(0,2,3);
    triangle_index tri2=triangle_index(3,2,5);
    triangle_index tri3=triangle_index(3,5,4);
    triangle_index tri4=triangle_index(4,5,6);
    triangle_index tri5=triangle_index(4,6,7);
    triangle_index tri6=triangle_index(1,2,6);
    triangle_index tri7=triangle_index(2,5,6);
    triangle_index tri8=triangle_index(0,3,7);
    triangle_index tri9=triangle_index(3,4,7);
    triangle_index tri10=triangle_index(0,7,1);
    triangle_index tri11=triangle_index(1,7,6);
    triangle_index index[]={tri0,tri1,tri2,tri3,tri4,tri5,tri6,tri7,tri8,tri9,tri10,tri11};
    
    info_object->nbr_triangle=11;
    
    //attribution d'un buffer de donnees (1 indique la crÃ©ation d'un buffer)-> envoie des donnÃ©es en mÃ©moire vidÃ©o
    glGenBuffers(1,&info_object->vbo); PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,info_object->vbo); PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,sizeof(geometrie),geometrie,GL_STATIC_DRAW); PRINT_OPENGL_ERROR();
    
    
    
    //attribution d'un autre buffer de donnees -> envoie des indices en mÃ©moire vidÃ©o
    glGenBuffers(1,&info_object->vboi); PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,info_object->vboi); PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW); PRINT_OPENGL_ERROR();
    
    charge_image("danger.tga",info_object,shader_id);


}
//
//void chargement_objet_5(info_object_opengl* info_object,GLuint shader_id)
//{
//    mesh m=load_obj_file("wateringcan.obj");
//    fill_color(&m,vec3(1.0f,1.0f,1.0f));
//
//   //transform vertices
//   mat4 T=mat4(0.5f,0.00f,0.00f,0.00f,
//                0.00f,0.5f,0.00f,0.00f,
//                0.00f,0.00f,0.5f,0.00f,
//                0.00f,0.00f,0.00f,1.00f);
//    mat4 R1=matrice_rotation(M_PI/2.0f,1.0f,0.0f,0.0f);
//    mat4 R2=matrice_rotation(M_PI,0.0f,1.0f,0.0f);
//
//    apply_deformation(&m,R2*R1*T);
//    update_normals(&m);
//    invert_normals(&m);
//
//    charge_image("brad.tga",info_object,shader_id);
//    charge_maillage_vbo(info_object,m);
//}


