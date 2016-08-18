#include "triangle.h"

void cgl_InitTriangle(Triangle* t, float vertices[], int size)
{
	t->VBO = 0;
	t->size = size;

	float texcoords[] = {
		0.0, 0.0,
		1.0, 0.0,
		0.5, 1.0,
	};

	glGenVertexArrays(1, &t->VAO);
	glGenBuffers(1, &t->VBO);

	glBindVertexArray(t->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, t->VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void cgl_DrawTriangle(Triangle* t, ShaderProgram* s)
{


	cgl_UseProgram(s);

	mat4x4 M;
	mat4x4_identity(M);
	mat4x4_translate(M, -0.5, 0.5, 0.0);
	mat4x4_rotate(M, M, 0.0, 0.0, 1.0, -glfwGetTime()*0.6);
	mat4x4_scale_aniso(M, M, 0.5, 0.5, 0.5);
	glUniformMatrix4fv(s->matpos, 1, GL_FALSE, *M);

	glBindVertexArray(t->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, t->VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (GLvoid*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	// glDisableVertexAttribArray(2);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
