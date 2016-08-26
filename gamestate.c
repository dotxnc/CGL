
#include "gamestate.h"

void cgl_InitGameState(GameState* state, const void* init, const void* update, const void* render)
{
	state->init = init;
	state->update = update;
	state->render = render;
	state->initialized = false;
}
