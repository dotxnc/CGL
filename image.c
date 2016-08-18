
#include "image.h"

void cgl_InitImage(Image* image, const char* path)
{
	float vertices[] = {
		/* Position      */ /* Color    */ /* TexCoords */
	    -0.5f, -0.5f, 0.0f,   1.0, 0.0, 0.0,   1.0, 1.0,
		-0.5f,  0.5f, 0.0f,   0.0, 1.0, 0.0,   1.0, 0.0,
	     0.5f,  0.5f, 0.0f,   0.0, 0.0, 1.0,   0.0, 0.0,
	     0.5f, -0.5f, 0.0f,   1.0, 1.0, 0.0,   0.0, 1.0

	};
	float texcoords[] = {
		0.0, 0.0,
		1.0, 0.0,
		0.5, 1.0
	};
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &image->VAO);
	glGenBuffers(1, &image->VBO);
	glGenBuffers(1, &image->EBO);

	glBindVertexArray(image->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, image->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, image->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	// load image
	glGenTextures(1, &image->texture);
	glBindTexture(GL_TEXTURE_2D, image->texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image->image = SOIL_load_image("data/container.jpg", &image->width, &image->height, 0, SOIL_LOAD_RGB);
	if (image->image) {
		printf("%d:%d\n", image->width, image->height);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image->image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// for (int i = 0; i < 16; i++) {
	// 	printf("%d  ", M2[i]);
	// 	if ((i+1)%4==0) {
	// 		printf("\n");
	// 	}
	// }
}

void cgl_DrawImage(Image* image, ShaderProgram* prog)
{

	cgl_UseProgram(prog);

	mat4x4 M;
	mat4x4_identity(M);
	mat4x4_rotate(M, M, 0.0, 0.0, 1.0, glfwGetTime()*0.6);
	mat4x4_scale_aniso(M, M, 0.5, 0.5, 0.5);
	glUniformMatrix4fv(prog->matpos, 1, GL_FALSE, *M);

	glBindVertexArray(image->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, image->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, image->EBO);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, image->texture);

	glBindVertexArray(image->VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);

}
