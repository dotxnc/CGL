#include "game.h"

static bool keys[1024];

void cgl_InitGame(Game* game, char* title, int width, int height)
{
	cgl_InitGameWindow(&game->window, title, width, height, false);
	game->use_vsync = true;
	game->lasttime = glfwGetTime();
	
	cgl_InitFrameBuffer(&game->framebuffer, width, height);
	
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
	
	while (!cgl_WindowShouldClose(&game->window))
	{
		cgl_BindFrameBuffer(&game->framebuffer);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glfwSwapInterval((int)game->use_vsync);
		
		if (game->current_state != NULL)
			game->current_state->update(game, game->delta);
		
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

void _cgl_keypressed(GLFWwindow* window, int key, int scan, int action, int mods)
{
	if (action == GLFW_PRESS) {
		keys[key] = true;
	} else if (action == GLFW_RELEASE) {
		keys[key] = false;
	}
}
