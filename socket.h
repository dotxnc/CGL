
#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define WITHOUT_SDL
#include <SDL2/SDL_net.h>

static bool init_sdl_net=true;

typedef struct test {
	int TYPE;
	float i;
	float j;
	double w;
} test;

typedef enum {
	CGL_SERVER,
	CGL_CLIENT
} CGL_SOCKET_TYPE;

typedef struct {
	int id;
}Client;

typedef struct {
	UDPsocket socket;
	UDPpacket* packet;
	IPaddress address;
	Client clients[16];
	CGL_SOCKET_TYPE type;
} Socket;

void cgl_InitSocket(Socket*, const char*, int, CGL_SOCKET_TYPE);
void cgl_UpdateSocket(Socket*);
// void cgl_SendSocket(Socket*, char*);
void cgl_SendSocket(Socket*, void*, unsigned int size);

#endif
