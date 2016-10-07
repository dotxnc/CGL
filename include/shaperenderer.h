#ifndef SHAPE_RENDERER_H
#define SHAPE_RENDERER_H

#include <GL/glew.h>
#include <linmath.h>
#include "window.h"
#include "shader.h"

typedef struct ShapeRenderer {
	// rectangle
	GLuint rect_VBO;
	GLuint rect_VAO;
	GLuint rect_EBO;
	
	// circle
	
	// line
	GLuint line_VBO;
	GLuint line_VAO;
	
	// other
	vec4 color;
	ShaderProgram* shader;
	
} ShapeRenderer;

void cgl_InitSR(ShapeRenderer*, ShaderProgram*);
void cgl_DrawLineSR(ShapeRenderer*, float, float, float, float);
void cgl_DrawRectSR(ShapeRenderer*, ShaderProgram*, float, float, int, int);
void cgl_DrawCircleSR(ShapeRenderer*, float, float, int);
void cgl_SetColorSR(ShapeRenderer*, float, float, float, float);

#endif /* end of include guard: SHAPE_RENDERER_H */
