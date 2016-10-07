#ifndef MODEL_H
#define MODEL_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "camera.h"
#include "shader.h"
#include "mesh.h"
#include "util/list.h"

#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

typedef struct Model {
	list meshes;
	int num_meshes=0;
	
	char* directory;
} Model;

void cgl_LoadModel(Model*, const char*);
void cgl_DrawModel(Model*, ShaderProgram*, Camera*, float, float, float);
void cgl_FreeModel(Model*);


static void _cgl_processnode(Model*, aiNode*, const aiScene*);
static Mesh* _cgl_processmesh(Model*, aiMesh*, const aiScene*);
static list* _cgl_loadmaterialtextures(Model*, aiMaterial*, aiTextureType, char*);


#endif /* end of include guard: MODEL_H */
