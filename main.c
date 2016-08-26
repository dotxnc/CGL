
#include <pthread.h>
#include "game.h"
#include "image.h"
#include "shader.h"
#include "font.h"
#include "lights.h"

static ShaderProgram main_shader;
static ShaderProgram text_shader;
static Image box3d;
static Camera cam;
static Font font;

unsigned int init()
{
	cgl_InitShaderProgram(&main_shader, "data/texture_vert.glsl", "data/texture_frag.glsl");
	cgl_InitShaderProgram(&text_shader, "data/text_vert.glsl", "data/text_frag.glsl");
	
	vec3 pos = {0, 0, 0};
	vec3 size = {1, 1, 1};
	cgl_InitImage(&box3d, "data/metal.jpg", "data/metal_specular.png", pos, size);
	cgl_InitCamera(&cam, 0, 0, 5);
	
	box3d.rx = -20;
	box3d.ry = 20;
	
	cgl_InitFont(&font, "data/font.ttf");
	
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

unsigned int update(float dt)
{
	if (cgl_IsKeyPressed(GLFW_KEY_F)) printf("key pressed f\n");
	if (cgl_IsKeyDown(GLFW_KEY_G)) printf("key down g\n");
	return 0;
}

unsigned int render(GameWindow* w)
{
	cam.aspect = cgl_GetWindowAspect(w);
	
	cgl_DrawImage(&box3d, &main_shader, &cam);
	
	vec3 tcolor = {0, 0, 0};
	cgl_DrawText(&font, &text_shader, "FUCK", 10, -20, 0.3, tcolor);
	
	return 0;
}

int main(int argc, char** argv)
{
	// srand(time(NULL));
	
	GameState test;
	cgl_InitGameState(&test, init, update, render);
	
	Game game;
	cgl_InitGame(&game, "3D Game", 800, 600);
	cgl_SetStateGame(&game, &test);
	cgl_StartGame(&game);
	
	cgl_DeleteLights();
	
	return 0;
}
