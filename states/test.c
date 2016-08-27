#include "test.h"

unsigned int test_init()
{
	cgl_InitShaderProgram(&main_shader, "data/texture_vert.glsl", "data/texture_frag.glsl");
	cgl_InitShaderProgram(&text_shader, "data/text_vert.glsl", "data/text_frag.glsl");
	
	vec3 pos = {0, 0, 0};
	vec3 size = {1, 1, 1};
	cgl_InitImage(&box, "data/metal.jpg", "data/metl_specular.png", pos, size);
	cgl_InitCamera(&cam, 0, 0, 5);
	
	cgl_InitFont(&font, "data/font.ttf");
	
	box.rx = -20;
	box.ry = 20;
	
	cgl_InitLights(4);
	for (int i = 0; i < 4; i++) {
		vec3 lpos = {1, 1, 1};
		vec3 lamb = {0.2, 0.2, 0.2};
		vec3 ldif = {0.8, 0.8, 0.8};
		vec3 spec = {1, 1, 1};
		cgl_AddLight(&main_shader, lpos, lamb, ldif, spec);
	}
	
	return 0;
}

unsigned int test_update(Game* game, float dt)
{
	
	return 0;
}

unsigned int test_render(GameWindow* window)
{
	cam.aspect = cgl_GetWindowAspect(window);
	
	cgl_DrawImage(&box, &main_shader, &cam);
	
	vec3 tcolor = {1, 1, 1};
	cgl_DrawText(&font, &text_shader, "FUCK", 10, 20, 0.3, tcolor);
	return 0;
}
