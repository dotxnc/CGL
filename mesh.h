#ifndef MESH_H
#define MESH_H

#include <stdio.h>
#include <linmath.h>
#include "window.h"
#include "shader.h"

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
	Vertex* vertices;
	GLuint* indices;
	Texture* textures;
	
	int num_vertices;
	int num_indices;
	int num_textures;
	
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
} Mesh;

void cgl_InitMesh(Mesh*, Vertex*, GLuint*, Texture*, int, int, int);
void cgl_DrawMesh(Mesh*, ShaderProgram*);

static void _cgl_setupmesh(Mesh*);

#endif /* end of include guard: MESH_H */
