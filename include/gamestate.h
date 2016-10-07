
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "window.h"
#include "game.h"

struct Game;

typedef unsigned int (*init_funct)();
typedef unsigned int (*update_funct)(struct Game*, float);
typedef unsigned int (*render_funct)(GameWindow*);
typedef unsigned int (*mousemoved_funct)(double, double);

typedef struct GameState {
	init_funct init;
	update_funct update;
	render_funct render;
	mousemoved_funct mousemoved;
	bool initialized;
} GameState;

void cgl_InitGameState(GameState*, const void*, const void*, const void*, const void*);

#endif
