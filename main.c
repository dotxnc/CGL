
#include "window.h"
#include "triangle.h"
#include "shader.h"
#include "gamestate.h"
#include "rectangle.h"
#include "image.h"

int main(int argc, char** argv)
{
	GameWindow window;
	int success = cgl_InitGameWindow(&window, "Test", 800, 600, false);
	if (success != 0) {
		return -1;
	}

	float verts[] = {
    -0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0,
     0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0,
     0.0f,  0.5f, 0.0f, 0.0, 0.0, 1.0
	};

	ShaderProgram t_prog;
	cgl_InitShaderProgram(&t_prog, "data/texture_vert.glsl", "data/texture_frag.glsl"); // for polygons

	ShaderProgram prog;
	cgl_InitShaderProgram(&prog, "data/vert.glsl", "data/frag.glsl"); // for untextured polygons

	Triangle tri;
	cgl_InitTriangle(&tri, verts, sizeof(verts));

	Image img;
	cgl_InitImage(&img, "", 0.0, 0.0, 1.0);

	Image* img_array;
	img_array = (Image*)malloc(10*sizeof(Image));
	cgl_InitImage(&img_array[0], "", 3.5, 0.0, -5.0);

	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	while (!cgl_WindowShouldClose(&window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1, 0.1, 0.1, 1.0);

		cgl_DrawImage(&img_array[0], &t_prog);
		cgl_DrawImage(&img, &t_prog);
		cgl_DrawTriangle(&tri, &prog);
		glfwSwapBuffers(window.window);
	}

	return 0;
}
