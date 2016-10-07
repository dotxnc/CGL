#include "shaperenderer.h"

void cgl_InitSR(ShapeRenderer* sr, ShaderProgram* shader)
{
// (shader = shader;
	
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	
	glGenVertexArrays(1, &sr->rect_VAO);
	glGenBuffers(1, &sr->rect_VBO);
	glGenBuffers(1, &sr->rect_EBO);
	
	glBindVertexArray(sr->rect_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, sr->rect_VBO);
	float vertices[] = {
		0,1, 0.0,
		0,1, 0.0,
		0,1, 0.0,
		0,1, 0.0,
		0,1, 0.0,
		0,1, 0.0
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void cgl_DrawRectSR(ShapeRenderer* sr, ShaderProgram* shader, float x, float y, int w, int h)
{
	cgl_UseProgram(shader);
	glDepthMask(false);
	
	mat4x4 ortho;
	mat4x4_identity(ortho);
	mat4x4_ortho(ortho, 0.0, _cgl_window_size[0], 0.0, _cgl_window_size[1], -1, 1);
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "projection"), 1, GL_FALSE, *ortho);
	glUniform4f(glGetUniformLocation(shader->program, "ucolor"), sr->color[0], sr->color[1], sr->color[2], sr->color[3]);
	
	glBindVertexArray(sr->rect_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, sr->rect_VBO);
	float vertices[] = {
		
		x,     y + h, 0.0,
		x,     y,     0.0,
		x + w, y,     0.0,
		x,     y + h, 0.0,
		x + w, y,     0.0,
		x + w, y + h, 0.0,
	};
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	
	glDepthMask(true);
}

void cgl_SetColorSR(ShapeRenderer* sr, float r, float g, float b, float a)
{
	sr->color[0] = r/255.f;
	sr->color[1] = g/255.f;
	sr->color[2] = b/255.f;
	sr->color[3] = a/255.f;
}
