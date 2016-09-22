
#define TINYOBJ_LOADER_C_IMPLEMENTATION

#include <pthread.h>
#include "game.h"
#include "image.h"
#include "shader.h"
#include "font.h"
#include "lights.h"
#include "sprite.h"

#include "states/splash.h"
#include "states/test.h"

int main(int argc, char** argv)
{
	cgl_InitGameState(&test_state, test_init, test_update, test_render, test_mousemoved);
	cgl_InitGameState(&splash_state, splash_init, splash_update, splash_render, splash_mousemoved);
	
	Game game;
	cgl_InitGame(&game, "3D Game", 1280, 720);
	cgl_SetStateGame(&game, &test_state);
	cgl_StartGame(&game);
	
	cgl_DeleteLights();
	
	return 0;
}
