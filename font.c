#include "font.h"

void cgl_InitFont(Font* font, const char* path)
{
	font->chars = (Character*)malloc(128*sizeof(Character));
	
	FT_Library ft;
	FT_Init_FreeType(&ft);
	
	FT_Face face;
	FT_New_Face(ft, path, 0, &face);
	FT_Set_Pixel_Sizes(face, 0, 48);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	for (int i = 0; i < 128; i++)
	{
		if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
			printf("Glyph failed to load: %c\n", (char)i);
			continue;
		}
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		vec2 s;
		vec2 b;
		
		Character c;
		c.index = i;
		c.size[0] = face->glyph->bitmap.width;
		c.size[1] = face->glyph->bitmap.rows;
		c.bearing[0] = face->glyph->bitmap_left;
		c.bearing[1] = face->glyph->bitmap_top;
		
		c.textureID = texture;
		c.advance = face->glyph->advance.x;
		font->chars[i] = c;
		
	}
	
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	
	glGenVertexArrays(1, &font->VAO);
	glGenBuffers(1, &font->VBO);
	
	glBindVertexArray(font->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, font->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6*4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
}

void cgl_DrawText(Font* font, ShaderProgram* shader, const char* text, float x, float y, float scale, vec3 color)
{
	cgl_UseProgram(shader);
	
	// ortho matrix for text
	mat4x4 ortho;
	mat4x4_identity(ortho);
	mat4x4_ortho(ortho, 0.0, 800, 0.0, 600, 0, 100);
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "projection"), 1, GL_FALSE, *ortho);
	
	glUniform3f(glGetUniformLocation(shader->program, "textColor"), color[0], color[1], color[2]);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(font->VAO);
	
	for (int i = 0; i < strlen(text); i++)
	{
		Character ch = font->chars[(int)text[i]];
		
		float xpos = x + ch.bearing[0] * scale;
		float ypos = y - (ch.size[1] - ch.bearing[1]) * scale;
		
		float w = ch.size[0] * scale;
		float h = ch.size[1] * scale;
		
		float vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },            
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }
		};
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		glBindBuffer(GL_ARRAY_BUFFER, font->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		x += (ch.advance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
}
