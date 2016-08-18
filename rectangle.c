
#include "rectangle.h"

void cgl_InitRectangle(Rectangle* rect, GameWindow* window, float x, float y, float w, float h)
{
	float vertices[] = {
		-0.9, -0.9, 0.0, // bottom left
		-0.9, -0.7, 0.0, // top left
		-0.7, -0.7, 0.0, // top right
		-0.7, -0.9, 0.0 // bottom right
	};
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &rect->VAO);
	glGenBuffers(1, &rect->VBO);
	glGenBuffers(1, &rect->EBO);

	glBindVertexArray(rect->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, rect->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rect->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void cgl_DrawRectangle(Rectangle* r, ShaderProgram* s)
{

	glBindVertexArray(r->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, r->VBO);
		// regenerate vertices for floating position
		float c = cos(glfwGetTime())*0.9;
		float vertices[] = {
			-0.1+c, -0.9, 0.0, 1.0, 0.0, 0.0, // bottom left
			-0.1+c, -0.7, 0.0, 0.0, 1.0, 0.0, // top left
			0.1+c, -0.7, 0.0, 0.0, 0.0, 1.0, // top right
			0.1+c, -0.9, 0.0, 1.0, 0.0, 1.0 // bottom right
		};
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->EBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0*sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (GLvoid*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
