
#ifndef FONT_H
#define FONT_H

#include <GL/glew.h>
#include <stdio.h>
#include <linmath.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "shader.h"

typedef struct {
	char index;
	GLuint textureID;
	vec2 size;
	vec2 bearing;
	GLint advance;
} Character;

typedef struct {
	GLuint VAO;
	GLuint VBO;
	Character* chars;
} Font;

void cgl_InitFont(Font*, const char*);
void cgl_DrawText(Font*, ShaderProgram*, const char*, float, float, float, vec3);
void cgl_DrawTextFmt(Font*, ShaderProgram*, float, float, float, vec3, const char*, ...);
void cgl_FreeFont(Font*);

#endif
