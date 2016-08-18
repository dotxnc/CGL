#include "window.h"

int cgl_InitGameWindow(GameWindow* window, char* title, int width, int height, bool resizable)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, resizable);

	window->window = glfwCreateWindow(width, height, title, NULL, NULL);
	window->width = width;
	window->height = height;

	glfwMakeContextCurrent(window->window);

	// init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		printf("%s\n", glewGetErrorString(err));
		return -1;
	}
}

bool cgl_WindowShouldClose(GameWindow* window)
{
	return glfwWindowShouldClose(window->window);
}

void cgl_DestroyWindow(GameWindow* window)
{
	glfwDestroyWindow(window->window);
}
