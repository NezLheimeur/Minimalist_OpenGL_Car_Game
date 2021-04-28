#ifndef OPENGL_AIDE_AFFICHAGE_HPP
#define OPENGL_AIDE_AFFICHAGE_HPP

#include <string>

struct mesh;
struct info_object_opengl;
struct mat4;
struct vec3;

/** demande l'affichage d'un objet a partir de info_object_opengl.
 * Une rotation et une translation sont passes en parametres. */
void affiche_objet(info_object_opengl info_object,GLuint shader_id,mat4 rotation,vec3 translation);

/** Charge une image designee par filename sur la carte graphique.
 *  L'identifiant de la texture est mise a jour dans la structure info_object_opengl. */
void charge_image(const std::string filename,info_object_opengl* info_object,GLuint shader_id);

/** Envoie un maillage complet sur la carte graphique afin qu'il soit pret a etre affiche. */
void charge_maillage_vbo(info_object_opengl* info_object,const mesh& m);

#endif
