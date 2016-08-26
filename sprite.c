#include "sprite.h"

void cgl_InitSprite(Sprite* sprite, const char* path)
{
	
	unsigned char* image;
	
	glGenTextures(1, &sprite->texture);
	glBindTexture(GL_TEXTURE_2D, sprite->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	image = SOIL_load_image(path, &sprite->width, &sprite->height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		sprite->width,
		sprite->height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image
	);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	
	// TODO: later
	glGenVertexArrays(1, &sprite->VAO);
	glGenBuffers(1, &sprite->VBO);
	
	glBindVertexArray(sprite->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, sprite->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6*4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void cgl_DrawSprite(Sprite* sprite, ShaderProgram* shader, float x, float y)
{
	cgl_UseProgram(shader);
	
	mat4x4 ortho;
	mat4x4_identity(ortho);
	mat4x4_ortho(ortho, 0.0, _cgl_window_size[0], 0.0, _cgl_window_size[1], -1, 1);
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "projection"), 1, GL_FALSE, *ortho);
	
	// glUniform3f(glGetUniformLocation(shader->program, "textColor"), 1, 1, 1);
	glActiveTexture(GL_TEXTURE0);
	
	glBindVertexArray(sprite->VAO);
	
	float vertices[6][4] = {
		{ x,                 y + sprite->height,   0.0, 0.0 },            
		{ x,                 y,                    0.0, 1.0 },
		{ x + sprite->width, y,                    1.0, 1.0 },
		{ x,                 y + sprite->height,   0.0, 0.0 },
		{ x + sprite->width, y,                    1.0, 1.0 },
		{ x + sprite->width, y + sprite->height,   1.0, 0.0 }
	};
	
	glBindTexture(GL_TEXTURE_2D, sprite->texture);
	glBindBuffer(GL_ARRAY_BUFFER, sprite->VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
}
