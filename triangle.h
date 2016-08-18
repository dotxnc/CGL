
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "window.h"
#include "shader.h"

typedef struct {
	GLuint VBO;
	GLuint VAO;
	int size;
} Triangle;

void cgl_InitTriangle(Triangle*, float[], int);
void cgl_DrawTriangle(Triangle*, ShaderProgram*);

#endif
