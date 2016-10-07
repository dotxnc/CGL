#ifndef BULLBOARD_H
#define BULLBOARD_H

#include <stdio.h>
#include <GL/glew.h>
#include <linmath.h>
#include "soil/SOIL.h"
#include "shader.h"
#include "window.h"
#include "camera.h"

typedef struct Billboard {
	float x,y,z;
	GLuint VAO;
	GLuint VBO;
	GLuint texture;
	int width,height;
} Billboard;

void cgl_InitBillboard(Billboard*, const char*, float, float, float);
void cgl_DrawBillboard(Billboard*, ShaderProgram*, Camera*);

#endif /* end of include guard: BULLBOARD_H */
