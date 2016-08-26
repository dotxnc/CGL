
#ifndef SPLASH_STATE_H
#define SPLASH_STATE_H

#include "../window.h"

static float timer;

unsigned int splash_init();
unsigned int splash_update(float);
unsigned int splash_render(GameWindow*);

#endif
