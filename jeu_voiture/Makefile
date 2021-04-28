CXXFLAGS= -g -Wall -Wextra -O2
LDFLAGS = -lm -lglut -lGLEW -lGLU -lGL -lpthread

all: executable

executable: main.o glutils.o mat4.o vec2.o vec3.o triangle_index.o vertex_opengl.o tga.o mesh.o opengl_aide_affichage.o scene.o
	g++ $^ -o executable $(LDFLAGS)


main.o: main.cpp glutils.hpp mat4.hpp vec3.hpp vec2.hpp triangle_index.hpp vertex_opengl.hpp image.hpp scene.hpp info_object_opengl.hpp mesh.hpp opengl_aide_affichage.hpp
glutils.o: glutils.cpp glutils.hpp
mat4.o: mat4.cpp mat4.hpp vec3.hpp
vec2.o: vec2.cpp vec2.hpp
vec3.o: vec3.cpp vec3.hpp
triangle_index.o: triangle_index.cpp triangle_index.hpp
vertex_opengl.o: vertex_opengl.cpp vertex_opengl.hpp vec2.hpp vec3.hpp
tga.o: tga.cpp image.hpp
mesh.o: mesh.cpp mesh.hpp mat4.hpp
opengl_aide_affichage.o: opengl_aide_affichage.cpp opengl_aide_affichage.hpp mat4.hpp vec3.hpp vec2.hpp glutils.hpp vertex_opengl.hpp image.hpp mesh.hpp
scene.o: scene.cpp scene.hpp info_object_opengl.hpp vec3.hpp vec2.hpp mat4.hpp vertex_opengl.hpp triangle_index.hpp image.hpp mesh.hpp opengl_aide_affichage.hpp glutils.hpp

clean: 
	rm -f *.o executable *~ 
