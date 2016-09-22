#ifndef MODEL_H
#define MODEL_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "camera.h"
#include "shader.h"

#include <float.h>
#include <limits.h>
#include <math.h>
#include <assert.h>

#ifdef _WIN64
#define atoll(S) _atoi64(S)
#include "util/windows-mmap.h"
#else
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#endif

#include "util/tinyobj_loader_c.h"

typedef struct Model {
	GLuint VAO;
	GLuint VBO;
	
	tinyobj_attrib_t    obj;
	tinyobj_shape_t*    shape;
	tinyobj_material_t* materials;
	
	size_t num_shapes;
	size_t num_materials;
	
} Model;

void cgl_LoadModel(Model*, const char*);

#endif /* end of include guard: MODEL_H */
