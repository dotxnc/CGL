
#include "gamestate.h"

void cgl_InitGameState(GameState* state, const void* init, const void* update, const void* render, const void* mousemoved)
{
	state->init = init;
	state->update = update;
	state->render = render;
	state->mousemoved = mousemoved;
	state->initialized = false;
}
