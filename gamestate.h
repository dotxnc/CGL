
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "window.h"

typedef unsigned int (*init_funct)();
typedef unsigned int (*update_funct)(float);
typedef unsigned int (*render_funct)(GameWindow*);

typedef struct {
	init_funct init;
	update_funct update;
	render_funct render;
} GameState;

void cgl_InitGameState(GameState*, const void*, const void*, const void*);

#endif
