/*****************************************************************************\
 * TP CPE, 3ETI, TP synthese d'images
 * --------------
 *
 * Programme principal des appels OpenGL
\*****************************************************************************/



#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>

#define GLEW_STATIC 1

#ifdef __APPLE__
#include <openGL/gl.h>		// Header File For The OpenGL32 Library
#include <openGL/glu.h>		// Header File For The GLu32 Library
#include <glut/glut.h>		// Header File For The GLut Library
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


#include "glutils.hpp"

#include "mat4.hpp"
#include "vec3.hpp"
#include "vec2.hpp"
#include "triangle_index.hpp"
#include "vertex_opengl.hpp"
#include "image.hpp"
#include "scene.hpp"
#include "info_object_opengl.hpp"
#include "mesh.hpp"
#include "opengl_aide_affichage.hpp"


/*****************************************************************************\
 * Variables globales
 *
 *
\*****************************************************************************/


//identifiant du shader
GLuint shader_program_id;

//variable temporelle
float temps_courant=0;
float translation_obstacle_x=0.0f;
float translation_obstacle_z=100.0f;
float translation_missile_x= 0.0f;
float translation_missile_z= 0.0f;

//booleans
bool chgt_obstacle=true;
bool obstacle_exist=true;
bool crash=false;
bool tir=false;
bool depart=false;


//les parametres de translations
float translation_x=0.0f;
float translation_y=0.0f;
float translation_z=0.0f;

float angle_x=0.0f;
float angle_y=0.0f;

//Matrice de rotation
mat4 rotation;

//Matrice de rotation animee pour le monstre
mat4 rotation_armadillo;

//mat4 rotation_voiture;
//Matrice de projection
mat4 projection;


info_object_opengl info_object_voiture;
info_object_opengl info_object_route;
info_object_opengl info_object_obstacle;
info_object_opengl info_object_projectile;
info_object_opengl info_object_ciel;
info_object_opengl info_object_herbe;

/*****************************************************************************\
 * Fonctions GLUT
 *
 *
\*****************************************************************************/


/*****************************************************************************\
 * init                                                                      *
\*****************************************************************************/
static void init()
{
    // Chargement du shader
    shader_program_id = read_shader("shader.vert", "shader.frag");

    //matrice de projection
    projection=matrice_projection(50.0f*M_PI/180.0f,1.0f,0.5f,100.0f);
    glUniformMatrix4fv(get_uni_loc(shader_program_id,"projection"),1,false,pointeur(projection)); PRINT_OPENGL_ERROR();

    chargement_voiture(&info_object_voiture,shader_program_id);
    chargement_route(&info_object_route,shader_program_id);

    chargement_obstacle(&info_object_obstacle,shader_program_id);
    chargement_projectile(&info_object_projectile,shader_program_id);
    chargement_objet_ciel(&info_object_ciel,shader_program_id);
    chargement_herbe(&info_object_herbe,shader_program_id);
    
    //activation de la gestion de la profondeur
    glEnable(GL_DEPTH_TEST); PRINT_OPENGL_ERROR();
    
    srand(time(NULL)); // initialisation de rand

}





//Fonction d'affichage
static void display_callback()
{
    //effacement des couleurs du fond d'ecran
    glClearColor(0.5f, 0.6f, 0.9f, 1.0f); PRINT_OPENGL_ERROR();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); PRINT_OPENGL_ERROR();
    
    
    //affichage
    
    glUniform2f(get_uni_loc(shader_program_id, "texture_translation"),0.0f, temps_courant); PRINT_OPENGL_ERROR();
    affiche_objet(info_object_route,shader_program_id,rotation,rotation*vec3(0.0f,0.0f,0.0f)); // affichage de la route
    affiche_objet(info_object_herbe,shader_program_id,rotation,rotation*vec3(0.0f,-0.1f,0.0f));// affichage de l'herbe gauche
    affiche_objet(info_object_herbe,shader_program_id,rotation,rotation*vec3(22.0f,-0.1f,0.0f));// affichage de l'herbe droite
 

    glUniform2f(get_uni_loc(shader_program_id, "texture_translation"),0.0f, 0.0f); PRINT_OPENGL_ERROR();
    affiche_objet(info_object_voiture,shader_program_id,rotation*matrice_rotation(1.57f,0.0f,1.0f,0.0f),rotation*(vec3(translation_x,translation_y,translation_z)+vec3(-0.0f,-0.5f,3.3f))); // affichage voiture
    affiche_objet(info_object_ciel,shader_program_id,rotation*matrice_rotation(-1.0f,1.0f,0.0f,0.0f),rotation*vec3(0.0f,-60.0f,-5.0f)); // affichage ciel
    
    
    if(obstacle_exist) // on verifie d'abord qu'un obstacle est present
    {
        if(chgt_obstacle) // autorise la modification du parametre x de chaque nouveau obstacle
        {
            translation_obstacle_x=( rand()/(float)RAND_MAX ) * (1.1f-(-1.3f)) + (-1.3f); // valeur aleatoire de x entre -1.3 et 1.1
            chgt_obstacle=false; // bloque l'accès au changement
        }
        affiche_objet(info_object_obstacle,shader_program_id,rotation,rotation*vec3(translation_obstacle_x,-0.2f,translation_obstacle_z)); // affiche l'obstacle
        if(!crash) // verifie la collision enrte la voiture et l'obstacle
       {
            if(translation_z>=translation_obstacle_z && ( (translation_x-0.175f<translation_obstacle_x+0.2f && translation_x-0.175f>translation_obstacle_x-0.2f) || (translation_x+0.175f<translation_obstacle_x+0.2f && translation_x+0.175f>translation_obstacle_x-0.2f) ))
            {
                crash=true;
                
            }
        
         if(tir) // si tir y'a on affiche un projectile si se projectile croise un obstacle les deux se detruisent mutuellement
          {
                affiche_objet(info_object_projectile,shader_program_id,rotation,rotation*vec3(translation_missile_x,-0.4f,translation_missile_z));
          
              if (translation_missile_z>=translation_obstacle_z && ((translation_missile_x-0.05f<translation_obstacle_x+0.2f && translation_missile_x-0.05f>translation_obstacle_x-0.2f) || (translation_missile_x+0.05f<translation_obstacle_x+0.2f && translation_missile_x+0.05f>translation_obstacle_x-0.2f) ))
              {
                  obstacle_exist=false;
                  tir=false;
              }
          }
        }
        else // si collision on quitte le jeu
        {
            exit(0);
        }
        
    }
    else // si pas d'obstacle le jeu continue normalement
    {
        if(tir)
        {
            affiche_objet(info_object_projectile,shader_program_id,rotation,rotation*vec3(translation_missile_x,-0.4f,translation_missile_z));
        }

    }



    //Changement de buffer d'affichage pour eviter un effet de scintillement
    glutSwapBuffers();
}


/*****************************************************************************\
 * keyboard_callback                                                         *
\*****************************************************************************/
static void keyboard_callback(unsigned char key, int, int)
{
    float d_angle=0.1f;

    //quitte le programme si on appuie sur les touches 'q', 'Q', ou 'echap'
    switch (key)
    {
    case 'q':
    case 'Q':
    case 27:
        exit(0);
        break;
    // peut tourner autour de l'axe x (la camera est fixe au bord de la route)
    case 'i':
        angle_x+=d_angle;
        break;
    case 'k':
        angle_x-=d_angle;
        break;
   
    // tir
    case 'p':
        tir=true;
        translation_missile_z=2.1f;
        translation_missile_x=translation_x+0.150f;
        break;
    
    // depart
    case 'd':
        depart=true;
        break;
     
    //pause
    case 'c':
        depart=false;
        break;
            
    }
    mat4 rotation_x=matrice_rotation(angle_x,1.0f,0.0f,0.0f);
    mat4 rotation_y=matrice_rotation(angle_y,0.0f,1.0f,0.0f);
    rotation=rotation_x*rotation_y;
}

/*****************************************************************************\
 * special_callback                                                          *
\*****************************************************************************/
static void special_callback(int key, int,int)
{
    float dL=0.03f;
    float dz=0.1f;
    
    //deplacement de la voiture sur l'axe x et z
    switch (key)
    {
          case GLUT_KEY_UP:
            
            if (translation_z<40.0f && depart==true) {
                translation_z+=dz; //avance
            }
            break;
            
        case GLUT_KEY_DOWN:
            
            if (translation_z>-2.00f && depart==true) {
                translation_z-=dz; //recule
            }
            break;
            
        case GLUT_KEY_LEFT:
            
            if (translation_x>-1.02f && depart==true) {
                 translation_x-=dL; // gauche
            }
        break;
            
        case GLUT_KEY_RIGHT:
            
             if (translation_x<0.72f && depart==true) {
            translation_x+=dL; // droite
             }
        break;
            
       
    
    }

    //reactualisation de l'affichage
    glutPostRedisplay();
}


/*****************************************************************************\
 * timer_callback                                                            *
\*****************************************************************************/
static void timer_callback(int)
{
    //demande de rappel de cette fonction dans 25ms
    glutTimerFunc(25, timer_callback, 0);

    //avancement du temps
    if (depart) {
        temps_courant=temps_courant+0.005f; // defile les textures de terrain
        translation_obstacle_z=translation_obstacle_z-0.5f; // defile des obstacle
        translation_missile_z=translation_missile_z+0.3f; // defile les projectiles
    }
    
    // nouvel obstacle quand celui sur l'écran disparait
    if (translation_obstacle_z==-5.0f) { 
        obstacle_exist=true;               
        translation_obstacle_z=100.0f;
        chgt_obstacle=true;
    }
    
    // missile diparait quand arrive au bout de l'ecran
    if (translation_missile_z==100.0f) {
        translation_missile_x=0;
        tir=false;
    }
    
    //reactualisation de l'affichage
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    //**********************************************//
    //Lancement des fonctions principales de GLUT
    //**********************************************//

    //initialisation
    glutInit(&argc, argv);

    //Mode d'affichage (couleur, gestion de profondeur, ...)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //Taille de la fenetre a l'ouverture
    glutInitWindowSize(600, 600);

    //Titre de la fenetre
    glutCreateWindow("OpenGL");

    //Fonction de la boucle d'affichage
    glutDisplayFunc(display_callback);

    //Fonction de gestion du clavier
    glutKeyboardFunc(keyboard_callback);

    //Fonction des touches speciales du clavier (fleches directionnelles)
    glutSpecialFunc(special_callback);

    //Fonction d'appel d'affichage en chaine
    glutTimerFunc(25, timer_callback, 0);

    //Initialisation des fonctions OpenGL
    #ifndef __APPLE__
    glewInit();
    #endif
    
    //Notre fonction d'initialisation des donnees et chargement des shaders
    init();


    //Lancement de la boucle (infinie) d'affichage de la fenetre
    glutMainLoop();

    //Plus rien n'est execute apres cela

    return 0;
}

