#include "window.h"

int cgl_InitGameWindow(GameWindow* window, char* title, int width, int height, bool resizable)
{
	_cgl_window_size[0] = width;
	_cgl_window_size[1] = height;
	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, resizable);

	window->window = glfwCreateWindow(width, height, title, NULL, NULL);
	window->width = width;
	window->height = height;

	glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

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
	glfwSetWindowShouldClose(window->window, true);
}

float cgl_GetWindowAspect(GameWindow* window)
{
	int w,h;
	glfwGetWindowSize(window->window, &w, &h);
	return (float)w/h;
}
