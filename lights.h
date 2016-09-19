
#ifndef LIGHTS_H
#define LIGHTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linmath.h>
#include "shader.h"

typedef struct {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
} PointLight;

PointLight* lights;
int _cgl_numlights;

void cgl_InitLights(int, ShaderProgram*);
void cgl_DeleteLights();
int cgl_AddLight(ShaderProgram*, vec3, vec3, vec3, vec3); // returns index
int cgl_DrawLight();

#endif
