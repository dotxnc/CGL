
#ifndef GAME_H
#define GAME_H

#include "window.h"
#include "gamestate.h"

typedef struct {
	GameWindow window;
	GameState* current_state;
	bool use_vsync;
	float delta;
	// TODO: framebuffers probably
} Game;

void cgl_InitGame(Game*, char*, int, int);
void cgl_SetStateGame(Game*, GameState*);
void cgl_StartGame(Game*);

#endif
