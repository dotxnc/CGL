#include "game.h"

static bool keys[1024];
static bool mbuttons[10];

void cgl_InitGame(Game* game, char* title, int width, int height)
{
	cgl_InitGameWindow(&game->window, title, width, height, false);
	game->use_vsync = true;
	game->lasttime = glfwGetTime();
	
	cgl_InitFrameBuffer(&game->framebuffer, width, height);
	
	_cgl_msupdt.needs_update = false;
	_cgl_msupdt.x = 0;
	_cgl_msupdt.y = 0;
	
}

void cgl_SetStateGame(Game* game, GameState* state)
{
	if (!state->initialized) {
		state->init();
		state->initialized = true;
	}
	game->current_state = state;
}

void cgl_StartGame(Game* game)
{
	glfwSetKeyCallback(game->window.window, _cgl_keypressed);
	glfwSetMouseButtonCallback(game->window.window, _cgl_mousepressed);
	glfwSetCursorPosCallback(game->window.window, _cgl_mousemoved);
	
	while (!cgl_WindowShouldClose(&game->window))
	{
		cgl_BindFrameBuffer(&game->framebuffer);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glfwSwapInterval((int)game->use_vsync);
		
		if (game->current_state != NULL)
			game->current_state->update(game, game->delta);
		
		if (game->current_state != NULL) {
			if (_cgl_msupdt.needs_update) {
				game->current_state->mousemoved(_cgl_msupdt.x, _cgl_msupdt.y);
				_cgl_msupdt.needs_update = false;
			}
		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2, 0.2, 0.2, 1.0);
		
		if (game->current_state != NULL)
			game->current_state->render(&game->window);
		
		cgl_DrawFrameBuffer(&game->framebuffer);
		
		glfwSwapBuffers(game->window.window);
		glfwPollEvents();
		
		float currenttime = glfwGetTime();
		game->delta = currenttime - game->lasttime;
		game->lasttime = currenttime;
		
		
	}
}

bool cgl_IsKeyDown(int key) {
	if (key < 1024 && key >= 0) {
		return keys[key];
	}
	return false;
}

bool cgl_IsKeyPressed(int key) {
	if (cgl_IsKeyDown(key)) {
		keys[key] = false;
		return true;
	}
	return false;
}

bool cgl_IsMouseDown(int mouse) {
	if (mouse >= 0 && mouse < 10) {
		return mbuttons[mouse];
	}
	return false;
}

bool cgl_IsMousePressed(int mouse) {
	if (cgl_IsMouseDown(mouse)) {
		mbuttons[mouse] = false;
		return true;
	}
	return false;
}

void _cgl_keypressed(GLFWwindow* window, int key, int scan, int action, int mods)
{
	if (action == GLFW_PRESS) {
		keys[key] = true;
	} else if (action == GLFW_RELEASE) {
		keys[key] = false;
	}
}

void _cgl_mousepressed(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) {
		mbuttons[button] = true;
	} else if (action == GLFW_RELEASE) {
		mbuttons[button] = false;
	}
}

void _cgl_mousemoved(GLFWwindow* window, double x, double y)
{
	if (x != _cgl_msupdt.x || y != _cgl_msupdt.y) {
		_cgl_msupdt.needs_update = true;
		_cgl_msupdt.x = x;
		_cgl_msupdt.y = y;
	}
}
