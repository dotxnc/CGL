#include "camera.h"

void cgl_InitCamera(Camera* cam, float x, float y, float z)
{
	cam->pos[0] = x;
	cam->pos[1] = y;
	cam->pos[2] = z;

	cam->front[0] = 0.0;
	cam->front[1] = 0.0;
	cam->front[2] = -1.0;

	cam->up[0] = 0.0;
	cam->up[1] = 1.0;
	cam->up[2] = 0.0;
	
	cam->aspect = 0;
	
	mat4x4_identity(cam->view);
	mat4x4_identity(cam->projection);
}

void cgl_LookAtCamera(Camera* cam, float x, float y, float z)
{
	vec3 pos = {x,y,z};
	mat4x4_look_at(cam->view, cam->pos, pos, cam->up);
}

void cgl_UpdateShaderCamera(Camera* cam, ShaderProgram* prog)
{
	cgl_UseProgram(prog);
	mat4x4_perspective(cam->projection, 45.0, cam->aspect, 0.01, 100.0);
	
	GLint viewLoc = glGetUniformLocation(prog->program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (*cam->view));
	GLint projLoc = glGetUniformLocation(prog->program, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, (*cam->projection));
	
	glUniform3f(glGetUniformLocation(prog->program, "viewPos"), cam->pos[0], cam->pos[1], cam->pos[2]);
}
