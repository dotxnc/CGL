#ifndef MODEL_H
#define MODEL_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "camera.h"
#include "shader.h"

#include "util/obj_parser.h"

typedef struct Model {
	GLuint VAO;
	GLuint VBO;
	
} Model;

void cgl_LoadModel(Model*, const char*);
void cgl_DrawModel(Model*, ShaderProgram*, Camera*, float, float, float);

#endif /* end of include guard: MODEL_H */
