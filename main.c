
#include "window.h"
#include "triangle.h"
#include "shader.h"
#include "gamestate.h"
#include "rectangle.h"
#include "image.h"
#include "font.h"

bool keys[1024];
float pitch,yaw,roll;
bool firstMouse = true;
float lastx = 400, lasty = 300;
bool capturemouse = false;

void key_callback(GLFWwindow* window, int key, int scan, int action, int mode)
{
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
	if (action == GLFW_PRESS && key == GLFW_KEY_TAB)
		capturemouse = !capturemouse;
}

float radians(float r) {
	return r * (M_PI/ 180.0 );
}

int main(int argc, char** argv)
{
	srand(time(NULL));

	pitch = yaw = roll = 0;

	GameWindow window;
	int success = cgl_InitGameWindow(&window, "OPENGL BITCHES", 1280, 720, false);
	if (success != 0) {
		return -1;
	}
	glfwSetKeyCallback(window.window, key_callback);

	float deltaTime = 0;
	float lastTime = glfwGetTime();

	float verts[] = {
    -0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0,
     0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0,
     0.0f,  0.5f, 0.0f, 0.0, 0.0, 1.0
	};

	ShaderProgram t_prog;
	cgl_InitShaderProgram(&t_prog, "data/texture_vert.glsl", "data/texture_frag.glsl"); // for polygons
	ShaderProgram prog;
	cgl_InitShaderProgram(&prog, "data/vert.glsl", "data/frag.glsl"); // for untextured polygons
	ShaderProgram text;
	cgl_InitShaderProgram(&text, "data/text_vert.glsl", "data/text_frag.glsl"); // for text
	
	Font font;
	cgl_InitFont(&font, "data/font.ttf");

	Camera cam;
	cgl_InitCamera(&cam, 0.0, 0.0, 5.0);

	Triangle tri;
	cgl_InitTriangle(&tri, verts, sizeof(verts));

	Image img;
	cgl_InitImage(&img, "", 0.0, 0.0, 1.0);

	Image* img_array;
	img_array = (Image*)malloc(10*sizeof(Image));
	cgl_InitImage(&img_array[0], "", 0.0f,  0.0f,  0.0f);
	cgl_InitImage(&img_array[1], "", 2.0f,  5.0f, -15.0f);
	cgl_InitImage(&img_array[2], "", -1.5f, -2.2f, -2.5f);
	cgl_InitImage(&img_array[3], "", -3.8f, -2.0f, -12.3f);
	cgl_InitImage(&img_array[4], "", 2.4f, -0.4f, -3.5f);
	cgl_InitImage(&img_array[5], "", -1.7f,  3.0f, -7.5f);
	cgl_InitImage(&img_array[6], "", 1.3f, -2.0f, -2.5f);
	cgl_InitImage(&img_array[7], "", 1.5f,  2.0f, -2.5f);
	cgl_InitImage(&img_array[8], "", 1.5f,  0.2f, -1.5f);
	cgl_InitImage(&img_array[9], "", -1.3f,  1.0f, -1.5f);


	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	while (!cgl_WindowShouldClose(&window))
	{
		int w,h;
		glfwGetWindowSize(window.window, &w, &h);
		cam.aspect = (float)w/h;
		
		if (capturemouse)
			glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		if (keys[GLFW_KEY_ESCAPE]) {
			cgl_DestroyWindow(&window);
			break;
		}
		
		if (capturemouse)
		{
			double xpos,ypos;
			glfwGetCursorPos(window.window, &xpos, &ypos);

			if(firstMouse)
			{
				lastx = xpos;
				lasty = ypos;
				firstMouse = false;
			}

			float xoffset = xpos-lastx;
			float yoffset = lasty-ypos;
			lastx = xpos;
			lasty = ypos;

			xoffset *= 0.05f;
			yoffset *= 0.05f;

			yaw += xoffset;
			pitch += yoffset;

			if (pitch > 89)
				pitch = 89;
			if (pitch < -89)
				pitch = -89;

			vec3 front;
			front[0] = (cos(radians(pitch)) * cos(radians(yaw)));
			front[1] = (sin(radians(pitch)));
			front[2] = (cos(radians(pitch)) * sin(radians(yaw)));
			vec3_norm(cam.front, front);
		}

		glfwPollEvents();
		if (keys[GLFW_KEY_W]) {
			vec3 newpos;
			for (int i=0;i<3;i++) {newpos[i]=cam.front[i]*(5.0*deltaTime);}
			vec3_add(cam.pos, cam.pos, newpos);
		}
		if (keys[GLFW_KEY_S]) {
			vec3 newpos;
			for (int i=0;i<3;i++) {newpos[i]=cam.front[i]*(5.0*deltaTime);}
			vec3_sub(cam.pos, cam.pos, newpos);
		}
		if (keys[GLFW_KEY_A]) {
			vec3 newpos;
			vec3_mul_cross(newpos, cam.front, cam.up);
			vec3_norm(newpos, newpos);
			newpos[0] *= 5.0 * deltaTime;
			newpos[1] *= 5.0 * deltaTime;
			newpos[2] *= 5.0 * deltaTime;
			vec3_sub(cam.pos, cam.pos, newpos);
		}
		if (keys[GLFW_KEY_D]) {
			vec3 newpos;
			vec3_mul_cross(newpos, cam.front, cam.up);
			vec3_norm(newpos, newpos);
			newpos[0] *= 5.0 * deltaTime;
			newpos[1] *= 5.0 * deltaTime;
			newpos[2] *= 5.0 * deltaTime;
			vec3_add(cam.pos, cam.pos, newpos);
		}


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1, 0.1, 0.1, 1.0);

		for (int i = 0; i < 10; i++)
			cgl_DrawImage(&img_array[i], &t_prog, &cam);
		// cgl_DrawTriangle(&tri, &prog);
		
		// Print debug data
		char debug_delta[512] = {0};
		sprintf(debug_delta, "Delta = %0.8f", deltaTime);
		char debug_fps[512] = {0};
		sprintf(debug_fps, "FPS = %0.1f", 1.0/deltaTime);
		char debug_capture[512] = {0};
		sprintf(debug_capture, "Capture Mouse = %s", capturemouse ? "true" : "false");
		
		vec3 textcolor;
		textcolor[0] = 0.7f;
		textcolor[1] = 0.7f;
		textcolor[2] = 0.7f;
		cgl_DrawText(&font, &text, "OPENGL", 10, 10, 0.3f, textcolor);
		cgl_DrawText(&font, &text, debug_delta, 10, 25, 0.3f, textcolor);
		cgl_DrawText(&font, &text, debug_capture, 10, 40, 0.3f, textcolor);
		cgl_DrawText(&font, &text, debug_fps, 10, 55, 0.3f, textcolor);
		
		// update buffers
		glfwSwapBuffers(window.window);

		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
	}

	for (int i = 0; i < 10; i++) {
		glDeleteBuffers(1, &img_array[i].VBO);
		glDeleteVertexArrays(1, &img_array[i].VAO);
	}

	return 0;
}
