
#ifndef CAMERA_H
#define CAMERA_H

#include <linmath.h>

typedef struct {
	vec3 pos;
	vec3 front;
	vec3 up;
} Camera;

void cgl_InitCamera(Camera*, float, float, float);

#endif
