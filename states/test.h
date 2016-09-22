
#ifndef TEST_STATE_H
#define TEST_STATE_H

#include "../gamestate.h"
#include "../window.h"
#include "../shader.h"
#include "../image.h"
#include "../font.h"
#include "../lights.h"
#include "../billboard.h"
#include "../model.h"

static ShaderProgram main_shader;
static ShaderProgram text_shader;
static ShaderProgram bill_shader;
static Image box;
static Image ground;
static Camera cam;
static Font font;
static Billboard board;
static Billboard blogo;
static int logo_light;
static Model model;

unsigned int test_init();
unsigned int test_update(Game*, float);
unsigned int test_render(GameWindow*);
unsigned int test_mousemoved(double, double);

extern GameState test_state;

#endif
