
#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>
#include <GL/glew.h>
#include <linmath.h>
#include "soil/SOIL.h"
#include "shader.h"
#include "window.h"

typedef struct {
	GLuint VAO;
	GLuint VBO;
	GLuint texture;
	
	int width,height;
} Sprite;

void cgl_InitSprite(Sprite*, const char*);
void cgl_DrawSprite(Sprite*, ShaderProgram*, float, float);

#endif
