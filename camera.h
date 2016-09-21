
#ifndef CAMERA_H
#define CAMERA_H

#define rads(x) x*3.14/180

#include <linmath.h>
#include "shader.h"

typedef struct {
	vec3 pos;
	vec3 front;
	vec3 up;
	vec3 vfront;
	float aspect;
	
	mat4x4 view;
	mat4x4 projection;
} Camera;

void cgl_InitCamera(Camera*, float, float, float);
void cgl_LookAtCamera(Camera*, float, float, float);
void cgl_UpdateShaderCamera(Camera*, ShaderProgram*);
void cgl_UpdateFPSCamera(Camera*, double, double);

#endif
