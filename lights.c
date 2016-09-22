#include "lights.h"

PointLight* lights;
int _cgl_numlights;

void cgl_InitLights(int max_lights, ShaderProgram* shader)
{
	lights = (PointLight*)malloc(max_lights*sizeof(PointLight));
	_cgl_numlights = 0;
	glUniform1i(glGetUniformLocation(shader->program, "usable_lights"), _cgl_numlights);
}

void cgl_DeleteLights()
{
	free(lights);
}

int cgl_AddLight(ShaderProgram* shader, vec3 pos, vec3 amb, vec3 dif, vec3 spec)
{
	glUniform1i(glGetUniformLocation(shader->program, "usable_lights"), _cgl_numlights+1);
	
	cgl_UseProgram(shader);
	
	lights[_cgl_numlights].position[0] = pos[0];
	lights[_cgl_numlights].position[1] = pos[1];
	lights[_cgl_numlights].position[2] = pos[2];
	
	lights[_cgl_numlights].ambient[0] = amb[0];
	lights[_cgl_numlights].ambient[1] = amb[1];
	lights[_cgl_numlights].ambient[2] = amb[2];
	
	lights[_cgl_numlights].diffuse[0] = dif[0];
	lights[_cgl_numlights].diffuse[1] = dif[1];
	lights[_cgl_numlights].diffuse[2] = dif[2];
	
	lights[_cgl_numlights].specular[0] = spec[0];
	lights[_cgl_numlights].specular[1] = spec[1];
	lights[_cgl_numlights].specular[2] = spec[2];
	
	char linear[128];
	char constant[128];
	char quadratic[128];
	char position[128];
	char ambient[128];
	char diffuse[128];
	char specular[128];
	
	sprintf(linear,     "pointLights[%d].linear",     _cgl_numlights);
	sprintf(constant,   "pointLights[%d].constant",   _cgl_numlights);
	sprintf(quadratic,  "pointLights[%d].quadratic",  _cgl_numlights);
	sprintf(position,   "pointLights[%d].position",   _cgl_numlights);
	sprintf(ambient,    "pointLights[%d].ambient",    _cgl_numlights);
	sprintf(diffuse,    "pointLights[%d].diffuse",    _cgl_numlights);
	sprintf(specular,   "pointLights[%d].specular",   _cgl_numlights);
	
	glUniform1f(glGetUniformLocation(shader->program, linear),     1.0);
	glUniform1f(glGetUniformLocation(shader->program, constant),   0.0014);
	glUniform1f(glGetUniformLocation(shader->program, quadratic),  0.000007);
	
	glUniform3f(glGetUniformLocation(shader->program, position),  pos[0],   pos[1],   pos[2]);
	glUniform3f(glGetUniformLocation(shader->program, diffuse),   dif[0],   dif[1],   dif[2]);
    glUniform3f(glGetUniformLocation(shader->program, ambient),   amb[0],   amb[1],   amb[2]);
    glUniform3f(glGetUniformLocation(shader->program, specular),  spec[0],  spec[1],  spec[2]);
	
	_cgl_numlights++;
	return _cgl_numlights-1;
}
