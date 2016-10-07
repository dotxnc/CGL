
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdio.h>
#include <GL/glew.h>
#include "shader.h"

typedef struct FrameBuffer {
	GLuint framebuffer;
	GLuint colortexture;
	GLuint renderbuffer;
	
	GLuint VAO;
	
	// TODO: REPLACE THIS
	ShaderProgram shader;
	
} FrameBuffer;

void cgl_InitFrameBuffer(FrameBuffer*, int, int);
void cgl_BindFrameBuffer(FrameBuffer*);
void cgl_DrawFrameBuffer(FrameBuffer*);

#endif
