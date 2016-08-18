
#ifndef SHADER_H
#define SHADER_H

#include "window.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
	GLuint program;
	GLint vertexpos;
	GLint colorpos;
	GLint matpos;
} ShaderProgram;

static const char* GetShaderSource(char*);
void cgl_InitShaderProgram(ShaderProgram*, char*, char*);
void cgl_UseProgram(ShaderProgram*);


#endif
