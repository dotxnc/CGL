#include "lights.h"

void cgl_InitLights(int max_lights)
{
	lights = (PointLight*)malloc(max_lights);
	_cgl_numlights = 0;
}

int cgl_AddLight(ShaderProgram* shader, vec3 pos, vec3 amb, vec3 dif, vec3 spec)
{
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
	
	glUniform1f(glGetUniformLocation(shader->program, "light.linear"), 1.0);
	glUniform1f(glGetUniformLocation(shader->program, "light.constant"), 0.0014);
	glUniform1f(glGetUniformLocation(shader->program, "light.quadratic"), 0.000007);
	glUniform3f(glGetUniformLocation(shader->program, "light.color"), 1.0, 0.2, 0.2);
	
	glUniform3f(glGetUniformLocation(shader->program, "light.position"), pos[0], pos[1], pos[2]);
	glUniform3f(glGetUniformLocation(shader->program, "light.ambient"), dif[0], dif[1], dif[2]);
    glUniform3f(glGetUniformLocation(shader->program, "light.diffuse"), amb[0], amb[1], amb[2]);
    glUniform3f(glGetUniformLocation(shader->program, "light.specular"), spec[0], spec[1], spec[2]);
	
	_cgl_numlights++;
	return _cgl_numlights-1;
}
