
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
	vec4 color;
	vec2 scale;
	int width,height;
} Sprite;

void cgl_InitSprite(Sprite*, const char*);

void cgl_DrawSprite(Sprite*, ShaderProgram*, float, float);
void cgl_DrawSpriteScale(Sprite*, ShaderProgram*, float, float, vec2);
void cgl_DrawSpriteColor(Sprite*, ShaderProgram*, float, float, vec4);
void cgl_DrawSpriteScaleColor(Sprite*, ShaderProgram*, float, float, vec2, vec4);

static void _cgl_drawsprite(Sprite*, ShaderProgram*, float, float, vec2, vec4);
#endif
