
#ifndef SPLASH_STATE_H
#define SPLASH_STATE_H

#include <stdio.h>
#include <math.h>
#include "../window.h"
#include "../sprite.h"
#include "../gamestate.h"

static float timer;
static float staytimer;
static int flag;
static float alpha;
static Sprite logo;
static Sprite powered;
static ShaderProgram shader;

unsigned int splash_init();
unsigned int splash_update(float);
unsigned int splash_render(GameWindow*);

GameState splash_state;

#endif
