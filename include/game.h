
#ifndef GAME_H
#define GAME_H

#define GLSL(src) "#version 330 core\n" #src

#include "window.h"
#include "gamestate.h"
#include "shader.h"
#include "framebuffer.h"

struct _cgl_mouseupdate {
	bool needs_update;
	double x,y;
};
static struct _cgl_mouseupdate _cgl_msupdt;

struct GameState;

typedef struct Game {
	GameWindow window;
	struct GameState* current_state;
	bool use_vsync;
	float delta;
	float lasttime;
	// TODO: framebuffers probably
	
	FrameBuffer framebuffer;
} Game;

void cgl_InitGame(Game*, char*, int, int);
void cgl_SetStateGame(Game*, struct GameState*);
void cgl_StartGame(Game*);

void cgl_SetCaptureMouse(Game*, bool);

bool cgl_IsKeyDown(int);
bool cgl_IsKeyPressed(int);

bool cgl_IsMouseDown(int);
bool cgl_IsMousePressed(int);

static void _cgl_keypressed(GLFWwindow*, int, int, int, int);
static void _cgl_mousepressed(GLFWwindow*, int, int, int);
static void _cgl_mousemoved(GLFWwindow*, double, double);

#endif
