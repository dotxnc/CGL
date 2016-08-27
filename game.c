#include "game.h"

static bool keys[1024];

void cgl_InitGame(Game* game, char* title, int width, int height)
{
	cgl_InitGameWindow(&game->window, title, width, height, false);
	game->use_vsync = true;
	game->lasttime = glfwGetTime();
	
	// Framebuffer stuff
	glGenFramebuffers(1, &game->framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, game->framebuffer);
	
	glGenTextures(1, &game->colorbuffer);
	glBindTexture(GL_TEXTURE_2D, game->colorbuffer);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, game->colorbuffer, 0);
	
	glGenRenderbuffers(1, &game->renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, game->renderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, game->renderbuffer);
	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
		printf("fuck yeah, framebuffer complete\n");
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	float quadVertices[] = {
	    -1.0f,  1.0f,  0.0f, 1.0f,
	     1.0f,  1.0f,  1.0f, 1.0f,
	     1.0f, -1.0f,  1.0f, 0.0f,

	     1.0f, -1.0f,  1.0f, 0.0f,
	    -1.0f, -1.0f,  0.0f, 0.0f,
	    -1.0f,  1.0f,  0.0f, 1.0f
	};
	
	cgl_InitShaderProgram(&game->frameshader, "data/framebuffer_vert.glsl", "data/framebuffer_frag.glsl");
	
	glGenVertexArrays(1, &game->frameVAO);
	glGenBuffers(1, &game->frameVBO);
	
	glBindVertexArray(game->frameVAO);
	glBindBuffer(GL_ARRAY_BUFFER, game->frameVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(glGetAttribLocation(game->frameshader.program, "position"));
	glVertexAttribPointer(glGetAttribLocation(game->frameshader.program, "position"), 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
	
	glEnableVertexAttribArray(glGetAttribLocation(game->frameshader.program, "texcoord"));
	glVertexAttribPointer(glGetAttribLocation(game->frameshader.program, "texcoord"), 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2 * sizeof(GLfloat)));
	glBindVertexArray(0);
	
	
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
		glBindFramebuffer(GL_FRAMEBUFFER, game->framebuffer);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glfwSwapInterval((int)game->use_vsync);
		
		if (game->current_state != NULL)
			game->current_state->update(game, game->delta);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2, 0.2, 0.2, 1.0);
		
		if (game->current_state != NULL)
			game->current_state->render(&game->window);\
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		glBindVertexArray(game->frameVAO);
		glDisable(GL_DEPTH_TEST);
		cgl_UseProgram(&game->frameshader);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, game->colorbuffer);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
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
