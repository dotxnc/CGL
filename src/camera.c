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

/// FPS CAMERA

static double _lastx;
static double _lasty;
static bool first = true;

static double yaw  =-90;
static double pitch=0;
static double roll =0;

void cgl_UpdateFPSCamera(Camera* cam, double mx, double my)
{
	if (first)
	{
		_lastx = mx;
		_lastx = my;
		first = false;
	}
	
	float xoff = mx - _lastx;
	float yoff = _lasty - my;
	_lastx = mx;
	_lasty = my;
	
	float sens = 0.05f;
	xoff *= sens;
	yoff *= sens;
	
	yaw += xoff;
	pitch += yoff;
	
	if (pitch > 89.f)
		pitch = 89.f;
	if (pitch < -89.f)
		pitch = -89.f;
	
	vec3 front;
	front[0] = cos(rads(yaw));
	front[1] = 0;
	front[2] = sin(rads(yaw));
	vec3_norm(cam->vfront, front);
	
	front[0] = cos(rads(pitch)) * cos(rads(yaw));
	front[1] = sin(rads(pitch));
	front[2] = cos(rads(pitch)) * sin(rads(yaw));
	vec3_norm(cam->front, front);
	
	
	// cam->front[0] = front[0];
	// cam->front[1] = front[1];
	// cam->front[2] = front[2];
	
}

void cgl_FreeCamera(Camera* camera)
{
	
}
