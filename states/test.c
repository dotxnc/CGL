#include "test.h"

unsigned int test_init()
{
	cgl_InitShaderProgram(&main_shader, "data/texture_vert.glsl", "data/texture_frag.glsl");
	cgl_InitShaderProgram(&text_shader, "data/text_vert.glsl", "data/text_frag.glsl");
	cgl_InitShaderProgram(&bill_shader, "data/billboard_vert.glsl", "data/billboard_frag.glsl");
	
	vec3 pos = {0, 0, 0};
	vec3 size = {1, 1, 1};
	// cgl_InitImage(&box, "data/metal.jpg", "data/metl_specular.png", pos, size);
	cgl_InitImage(&box, "data/metal.jpg", "data/SpecularMap.png", pos, size);
	
	vec3 gpos = {0, -1, 0};
	vec3 gsize = {7, 0.1, 7};
	cgl_InitImage(&ground, "data/metal.jpg", "data/metal_specular.png", gpos, gsize);
	cgl_InitCamera(&cam, 0, 0, 5);
	
	cgl_InitFont(&font, "data/font.ttf");
	
	cgl_InitBillboard(&board, "data/light.png", 0, 0, 2);
	cgl_InitBillboard(&blogo, "data/logo.png", 0, 2, 0);
	
	// box.rx = -20;
	// box.ry = 20;
	
	cgl_InitLights(100, &main_shader);
	vec3 lpos = {1, 0, 2};
	vec3 lamb = {0.1, 0.1, 0.1};
	vec3 ldif = {0.8, 0.5, 0.8};
	vec3 spec = {1, 1, 1};
	// cgl_AddLight(&main_shader, lpos, lamb, ldif, spec);
	lpos[1] = 0;
	cgl_AddLight(&main_shader, lpos, lamb, ldif, spec);
	lpos[0] = -1;
	cgl_AddLight(&main_shader, lpos, lamb, ldif, spec);
	
	return 0;
}

unsigned int test_update(Game* game, float dt)
{
	box.x = cos(glfwGetTime())*2;
	// cam.pos[1] = sin(glfwGetTime());
	// cam.pos[0] = sin(0.7*glfwGetTime());
	// cam.pos[2] = sin(0.4*glfwGetTime())*5;
	
	blogo.x = box.x-0.2;
	blogo.y = 0.5;
	blogo.z = -1;
	
	cgl_LookAtCamera(&cam, cam.pos[0]+cam.front[0], cam.pos[1]+cam.front[1], cam.pos[2]+cam.front[2]);
	
	int spd = 3;
	
	if (cgl_IsKeyDown(GLFW_KEY_W)) {
		vec3 speed = {0, 0, -spd*dt};
		vec3_add(cam.pos, cam.pos, speed);
	}
	if (cgl_IsKeyDown(GLFW_KEY_S)) {
		vec3 speed = {0, 0, spd*dt};
		vec3_add(cam.pos, cam.pos, speed);
	}
	if (cgl_IsKeyDown(GLFW_KEY_A)) {
		vec3 speed = {-spd*dt, 0, 0};
		vec3_add(cam.pos, cam.pos, speed);
	}
	if (cgl_IsKeyDown(GLFW_KEY_D)) {
		vec3 speed = {spd*dt, 0, 0};
		vec3_add(cam.pos, cam.pos, speed);
	}
	if (cgl_IsKeyDown(GLFW_KEY_SPACE)) {
		vec3 speed = {0, spd*dt, 0};
		vec3_add(cam.pos, cam.pos, speed);
	}
	if (cgl_IsKeyDown(GLFW_KEY_LEFT_CONTROL)) {
		vec3 speed = {0, -spd*dt, 0};
		vec3_add(cam.pos, cam.pos, speed);
	}
	
	return 0;
}

unsigned int test_render(GameWindow* window)
{
	cam.aspect = cgl_GetWindowAspect(window);
	cgl_UpdateShaderCamera(&cam, &main_shader);
	cgl_UpdateShaderCamera(&cam, &bill_shader);
	
	cgl_DrawImage(&box, &main_shader, &cam);
	cgl_DrawImage(&ground, &main_shader, &cam);
	
	board.x = 1;
	cgl_DrawBillboard(&board, &bill_shader, &cam);
	board.x = -1;
	cgl_DrawBillboard(&board, &bill_shader, &cam);
	
	cgl_DrawBillboard(&blogo, &bill_shader, &cam);
	
	vec3 tcolor = {1, 1, 1};
	cgl_DrawText(&font, &text_shader, "FUCK", 10, 20, 0.3, tcolor);
	return 0;
}

unsigned int test_mousemoved(double x, double y)
{
	printf("mouse_moved: %0.0fx%0.0f\n", x, y);
}
