#ifndef MESH_H
#define MESH_H

#include <stdio.h>
#include <linmath.h>
#include "window.h"
#include "shader.h"

#include "util/list.h"

typedef struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
} Vertex;

typedef struct Texture {
	GLuint id;
	char* type;
} Texture;

typedef struct Mesh {
	list vertices;
	list indices;
	list textures;
	
	int num_vertices;
	int num_indices;
	int num_textures;
	
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
} Mesh;

void cgl_InitMesh(Mesh*, list, list, list, int, int, int);
void cgl_DrawMesh(Mesh*, ShaderProgram*);
void cgl_FreeMesh(Mesh*);

static void _cgl_setupmesh(Mesh*);

#endif /* end of include guard: MESH_H */
