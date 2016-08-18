
#ifndef IMAGE_H
#define IMAGE_H

#include "window.h"
#include "shader.h"
#include "soil/SOIL.h"

typedef struct {
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	int size;

	int width,height;
	unsigned char* image;
	GLuint texture;
} Image;

void cgl_InitImage(Image*, const char*);
void cgl_DrawImage(Image*, ShaderProgram*);

#endif
