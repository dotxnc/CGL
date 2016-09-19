
#ifndef CAMERA_H
#define CAMERA_H

#include <linmath.h>
#include "shader.h"

typedef struct {
	vec3 pos;
	vec3 front;
	vec3 up;
	float aspect;
	
	mat4x4 view;
	mat4x4 projection;
} Camera;

void cgl_InitCamera(Camera*, float, float, float);
void cgl_LookAtCamera(Camera*, float, float, float);
void cgl_UpdateShaderCamera(Camera*, ShaderProgram*);

#endif
