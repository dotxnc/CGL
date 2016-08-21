
#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define WITHOUT_SDL
#include <SDL2/SDL_net.h>

#define _cgl_debug() printf("DEBUG ON LINE %d\n", __LINE__)

static bool init_sdl_net=true;

typedef void(*socket_recv)();
typedef void(*socket_conn)();
typedef void(*socket_dconn)();

typedef enum
{
	CGL_CLIENTDATA = 125,
	CGL_CONNECTION = 126,
	CGL_CONNECT = 127,
	CGL_DISCONNECT = 128
} CGL_PACKET_TYPE;

typedef struct { CGL_PACKET_TYPE type; CGL_PACKET_TYPE data; } _cgl_connection;
typedef struct { CGL_PACKET_TYPE type; int id; } _cgl_clientdata;

typedef enum {
	CGL_SERVER,
	CGL_CLIENT
} CGL_SOCKET_TYPE;

typedef struct {
	int        id;
	IPaddress  addr;
}Client;

typedef struct {
	CGL_SOCKET_TYPE  type;
	UDPsocket        socket;
	UDPpacket*       packet;
	IPaddress        address;
	Client           clients[16];
	int              numclients;
	int              ID;
	// callbacks
	socket_recv      callback_recv;
	socket_conn      callback_conn;
	socket_dconn     callback_dconn;
} Socket;

void cgl_InitSocket(Socket*, const char*, int, CGL_SOCKET_TYPE);
void cgl_UpdateSocket(Socket*);
void cgl_SendSocket(Socket*, void*, unsigned int size);
void cgl_SetCallbackSocket(Socket*, socket_recv, socket_conn, socket_dconn);

// private cgl network functions
static void _cgl_getclient(Socket*, IPaddress);
static void _cgl_sendtoclient(Socket*, IPaddress, void*, unsigned int);

#endif
