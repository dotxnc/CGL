#include "billboard.h"

void cgl_InitBillboard(Billboard* bill, const char* file, float x, float y, float z)
{
	bill->x = x;
	bill->y = y;
	bill->z = z;
	
	unsigned char* image;
	
	glGenTextures(1, &bill->texture);
	glBindTexture(GL_TEXTURE_2D, bill->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	image = SOIL_load_image(file, &bill->width, &bill->height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bill->width, bill->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	
	glGenVertexArrays(1, &bill->VAO);
	glGenBuffers(1, &bill->VBO);
	
	glBindVertexArray(bill->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, bill->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6*5, NULL, GL_DYNAMIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3*sizeof(float)));
	glEnableVertexAttribArray(2);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void cgl_DrawBillboard(Billboard* bill, ShaderProgram* shader, Camera* cam)
{
	
	cgl_UseProgram(shader);
	// glDepthMask(false);
	// glDisable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5);
	
	vec3 pos = {bill->x, bill->y, bill->z};
	
	mat4x4 model;
	mat4x4_identity(model);
	mat4x4_translate(model, bill->x, bill->y, bill->z);
	
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "model"), 1, GL_FALSE, *model);
	
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(bill->VAO);
	
	float dx = bill->width/1280.f;
	float dy = bill->height/1280.f;
	
	float vertices[6][5] = {
		{ 0 -dx/2, dy-dy/2, 0,    0.0, 0.0},
		{ 0 -dx/2, 0 -dy/2, 0,    0.0, 1.0},
		{ dx-dx/2, 0 -dy/2, 0,    1.0, 1.0},
		{ 0 -dx/2, dy-dy/2, 0,    0.0, 0.0},
		{ dx-dx/2, 0 -dy/2, 0,    1.0, 1.0},
		{ dx-dx/2, dy-dy/2, 0,    1.0, 0.0}
	};
	
	glBindTexture(GL_TEXTURE_2D, bill->texture);
	glBindBuffer(GL_ARRAY_BUFFER, bill->VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glDisable(GL_ALPHA_TEST);
	glDepthMask(true);
	
}
