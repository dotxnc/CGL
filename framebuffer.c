#include "framebuffer.h"

void cgl_InitFrameBuffer(FrameBuffer* buffer, int width, int height)
{
	glGenFramebuffers(1, &buffer->framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, buffer->framebuffer);
	
	glGenTextures(1, &buffer->colortexture);
	glBindTexture(GL_TEXTURE_2D, buffer->colortexture);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buffer->colortexture, 0);
	
	glGenRenderbuffers(1, &buffer->renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, buffer->renderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, buffer->renderbuffer);
	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
		printf("Framebuffer complete.\n");
	} else printf("Framebuffer incomplete!\n");
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	float quad[] = {
	    -1.0f,  1.0f,  0.0f, 1.0f,
	     1.0f,  1.0f,  1.0f, 1.0f,
	     1.0f, -1.0f,  1.0f, 0.0f,

	     1.0f, -1.0f,  1.0f, 0.0f,
	    -1.0f, -1.0f,  0.0f, 0.0f,
	    -1.0f,  1.0f,  0.0f, 1.0f
	};
	
	cgl_InitShaderProgram(&buffer->shader, "data/framebuffer_vert.glsl", "data/framebuffer_frag.glsl");
	
	GLuint _VBO;
	glGenVertexArrays(1, &buffer->VAO);
	glGenBuffers(1, &_VBO);
	
	glBindVertexArray(buffer->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(glGetAttribLocation(buffer->shader.program, "position"));
	glVertexAttribPointer(glGetAttribLocation(buffer->shader.program, "position"), 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
	
	glEnableVertexAttribArray(glGetAttribLocation(buffer->shader.program, "texcoord"));
	glVertexAttribPointer(glGetAttribLocation(buffer->shader.program, "texcoord"), 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(GLfloat)));
	glBindVertexArray(0);
	
}

void cgl_BindFrameBuffer(FrameBuffer* buffer)
{
	if (buffer != NULL) {
		glBindFramebuffer(GL_FRAMEBUFFER, buffer->framebuffer);
	} else glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void cgl_DrawFrameBuffer(FrameBuffer* buffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glBindVertexArray(buffer->VAO);
	glDisable(GL_DEPTH_TEST);
	cgl_UseProgram(&buffer->shader);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, buffer->colortexture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
