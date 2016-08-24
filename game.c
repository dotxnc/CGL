#include "game.h"

void cgl_InitGame(Game* game, char* title, int width, int height)
{
	cgl_InitGameWindow(&game->window, title, width, height, false);
	game->use_vsync = true;
}

void cgl_SetStateGame(Game* game, GameState* state)
{
	game->current_state = state;
}

void cgl_StartGame(Game* game)
{
	glEnable(GL_DEPTH_TEST);
	while (!cgl_WindowShouldClose(&game->window))
	{
		glfwSwapInterval((int)game->use_vsync);
		
		if (game->current_state != NULL)
			game->current_state->update(game->delta);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2, 0.2, 0.2, 1.0);
		
		if (game->current_state != NULL)
			game->current_state->render(&game->window);
		
		glfwSwapBuffers(game->window.window);
		glfwPollEvents();
		
	}
}
