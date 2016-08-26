
#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <stdbool.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <linmath.h>

typedef struct {
	GLFWwindow* window;
	int width;
	int height;
} GameWindow;

vec2 _cgl_window_size;

int cgl_InitGameWindow(GameWindow*, char*, int, int, bool);
bool cgl_WindowShouldClose(GameWindow*);
void cgl_DestroyWindow(GameWindow*);

float cgl_GetWindowAspect(GameWindow*);

#endif
