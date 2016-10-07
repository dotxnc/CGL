#include "test.h"

GameState test_state;

unsigned int test_init()
{
	cgl_InitShaderProgram(&main_shader, "data/texture_vert.glsl", "data/texture_frag.glsl");
	cgl_InitShaderProgram(&text_shader, "data/text_vert.glsl", "data/text_frag.glsl");
	cgl_InitShaderProgram(&bill_shader, "data/billboard_vert.glsl", "data/billboard_frag.glsl");
	cgl_InitShaderProgram(&shape_shader, "data/shape_vert.glsl", "data/shape_frag.glsl");
	cgl_InitShaderProgram(&sprite_shader, "data/sprite_vert.glsl", "data/sprite_frag.glsl");
	
	cgl_InitSR(&sr, &shape_shader);
	
	vec3 pos = {0, 0, 0};
	vec3 size = {1, 1, 1};
	// cgl_InitImage(&box, "data/metal.jpg", "data/metl_specular.png", pos, size);
	cgl_InitImage(&box, "data/metal.jpg", "data/metal_specular.png", pos, size);
	
	vec3 gpos = {0, -1, 0};
	vec3 gsize = {7, 0.1, 7};
	cgl_InitImage(&ground, "data/metal.jpg", "data/metal_specular.png", gpos, gsize);
	cgl_InitCamera(&cam, 0, 0, 5);
	
	cgl_InitFont(&font, "data/font.ttf");
	
	cgl_InitBillboard(&board, "data/light.png", 0, 0, 2);
	cgl_InitBillboard(&blogo, "data/logo.png", 0, 2, 0);
	
	cgl_InitLights(100, &main_shader);
	vec3 lpos = {1, 0, 2};
	vec3 lamb = {0.1, 0.1, 0.1};
	vec3 ldif = {0.8, 0.5, 0.8};
	vec3 spec = {1, 1, 1};
	cgl_AddLight(&main_shader, lpos, lamb, ldif, spec);
	lpos[0] = -1;
	cgl_AddLight(&main_shader, lpos, lamb, ldif, spec);
	lpos[0] = 0;
	lpos[2] = -2;
	cgl_AddLight(&main_shader, lpos, lamb, ldif, spec);
	
	//cgl_LoadModel(&model, "data/airboat.obj");
	
	return 0;
}

unsigned int test_update(Game* game, float dt)
{
    cgl_SetCaptureMouse(game, true);
	
	box.x = cos(glfwGetTime())*2;
	
	blogo.x = box.x;
	blogo.y = 0.9;
	
	cgl_LookAtCamera(&cam, cam.pos[0]+cam.front[0], cam.pos[1]+cam.front[1], cam.pos[2]+cam.front[2]);
	
	float spd = 5.f;
	
	if (cgl_IsKeyDown(GLFW_KEY_W)) {
		vec3 dir;
		for(int i=0;i<3;i++) dir[i]=cam.vfront[i]*(spd*dt);
		vec3_add(cam.pos, cam.pos, dir);
	}
	if (cgl_IsKeyDown(GLFW_KEY_S)) {
		vec3 dir;
		for(int i=0;i<3;i++) dir[i]=cam.vfront[i]*(spd*dt);
		vec3_sub(cam.pos, cam.pos, dir);
	}
	if (cgl_IsKeyDown(GLFW_KEY_A)) {
		vec3 dir;
		vec3_mul_cross(dir, cam.vfront, cam.up);
		vec3_norm(dir, dir);
		dir[0] *= spd * dt;
		dir[1] *= spd * dt;
		dir[2] *= spd * dt;
		vec3_sub(cam.pos, cam.pos, dir);
	}
	if (cgl_IsKeyDown(GLFW_KEY_D)) {
		vec3 dir;
		vec3_mul_cross(dir, cam.vfront, cam.up);
		vec3_norm(dir, dir);
		dir[0] *= spd * dt;
		dir[1] *= spd * dt;
		dir[2] *= spd * dt;
		vec3_add(cam.pos, cam.pos, dir);
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
	
	board.y = 0;
	board.z = 2;
	board.x = 1;
	cgl_DrawBillboard(&board, &bill_shader, &cam);
	board.x = -1;
	cgl_DrawBillboard(&board, &bill_shader, &cam);
	board.x = 0;
	board.y = 1.5;
	board.z = -2;
	cgl_DrawBillboard(&board, &bill_shader, &cam);
	
	cgl_DrawBillboard(&blogo, &bill_shader, &cam);
	
	cgl_DrawModel(&model, &main_shader, &cam, 0, 0, 0);
	
	cgl_SetColorSR(&sr, 255, 0, 0, 255);
	cgl_DrawRectSR(&sr, &shape_shader, 10, 20, 50, 10);
	cgl_DrawRectSR(&sr, &shape_shader, 10, 40, 50*4, 10);
	
	vec3 tcolor = {1, 1, 1};
	cgl_DrawText(&font, &text_shader, "FUCK", 10, 20, 0.3, tcolor);
	cgl_DrawTextFmt(&font, &text_shader, 10, 40, 0.3, tcolor, "Player Pos: %.2f %.2f %.2f", cam.pos[0], cam.pos[1], cam.pos[2]);
	return 0;
}

unsigned int test_mousemoved(double x, double y)
{
	cgl_UpdateFPSCamera(&cam, x, y);
}
