
#include <pthread.h>
#include "game.h"

unsigned int init()
{
	
	return 0;
}

unsigned int update(float dt)
{
	
	return 0;
}

unsigned int render(GameWindow* w)
{
	
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
	
	return 0;
}
