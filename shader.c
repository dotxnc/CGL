
#include "shader.h"

const char* GetShaderSource(char* path)
{
	char* buffer = 0;
	long length;

	FILE* f = fopen(path, "rb");

	if (f)
	{
		fseek(f, 0, SEEK_END);
		length = ftell(f);
		fseek(f, 0, SEEK_SET);
		rewind(f);
		buffer = malloc(length * (sizeof(char)));
		if (buffer) {
			fread(buffer, sizeof(char), length, f);
		}
		fclose(f);
		buffer[length-1] = '\0';
	}

	printf("%s\n\n", buffer);

	return buffer;
}

void cgl_InitShaderProgram(ShaderProgram* prog, char* vpath, char* fpath)
{
	printf("VERTEX SHADER\n");
	const char* vsource = GetShaderSource(vpath);
	printf("FRAGMENT SHADER\n");
	const char* fsource = GetShaderSource(fpath);

	if (!vsource || !fsource) {
		printf("Failed to create shader program. missing shader source.\n");
		return;
	}

	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &vsource, NULL);
	glCompileShader(vshader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &success);
	if(!success) {
	    glGetShaderInfoLog(vshader, 512, NULL, infoLog);
	    printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
	}

	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &fsource, NULL);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &success);
	if(!success) {
	    glGetShaderInfoLog(fshader, 512, NULL, infoLog);
	    printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
	}

	prog->program = glCreateProgram();
	glAttachShader(prog->program, vshader);
	glAttachShader(prog->program, fshader);
	glBindFragDataLocation(prog->program, 0, "outColor");
	glLinkProgram(prog->program);

	prog->vertexpos = glGetAttribLocation(prog->program, "position");

	glDeleteShader(vshader);
	glDeleteShader(fshader);
}

void cgl_UseProgram(ShaderProgram* p)
{
	glUseProgram(p->program);
}
