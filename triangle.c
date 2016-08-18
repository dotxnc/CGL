#include "triangle.h"

void cgl_InitTriangle(Triangle* t, float vertices[], int size)
{
	t->VBO = 0;
	t->size = size;

	glGenVertexArrays(1, &t->VAO);

	glBindVertexArray(t->VAO);
	glGenBuffers(1, &t->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, t->VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void cgl_DrawTriangle(Triangle* t, ShaderProgram* s)
{
	glBindVertexArray(t->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, t->VBO);
	glVertexAttribPointer(s->vertexpos, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(s->vertexpos);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
