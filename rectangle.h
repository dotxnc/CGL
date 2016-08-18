
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "window.h"
#include "shader.h"
#include <math.h>

typedef struct {
	float x,y,w,h;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
} Rectangle;

void cgl_InitRectangle(Rectangle*, GameWindow*, float, float, float, float);
void cgl_DrawRectangle(Rectangle*, ShaderProgram*);

#endif
