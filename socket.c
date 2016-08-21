#include "socket.h"

void cgl_InitSocket(Socket* _socket, const char* ip, int port, CGL_SOCKET_TYPE type)
{
	if (init_sdl_net) SDLNet_Init();
	
	_socket->type = type;
	
	if (type == CGL_SERVER) {
		_socket->socket = SDLNet_UDP_Open(port);
		SDLNet_ResolveHost(&_socket->address, NULL, port);
	}
	else if (type == CGL_CLIENT) {
		_socket->socket = SDLNet_UDP_Open(0);
		SDLNet_ResolveHost(&_socket->address, ip, port);
	}
	
	if (_socket->socket == NULL) {
		printf("Socket not created, %d, %d\n", type);
		return;
	}
	
	_socket->packet = SDLNet_AllocPacket(256);
}

void cgl_UpdateSocket(Socket* _socket)
{
	if (SDLNet_UDP_Recv(_socket->socket, _socket->packet))
	{
		char* data = (char*)malloc(_socket->packet->len);
		memcpy(data, _socket->packet->data, _socket->packet->len);
		
		if (data[0] == 123) {
			
			test t2;
			memcpy(&t2, _socket->packet->data, sizeof(t2));
			printf("SERV packet of type %d \"test\"\n\t: t.type = %d \n\t: test.i = %0.2f \n\t: test.j = %0.2f \n\t: test.w = %f\n", strlen(_socket->packet->data), t2.TYPE, t2.i, t2.j, t2.w);
		}
	}
}

void cgl_SendSocket(Socket* _socket, void* data, unsigned int size)
{
	char* buffer = (char*)malloc(size);
	memcpy(buffer, &data, size);
	printf("%d %d %d %d\n", sizeof(data), sizeof(buffer), sizeof(test), size);
	
	UDPpacket tosend;
	tosend.len = size;
	tosend.data = (Uint8*)malloc(sizeof(buffer));
	tosend.address.host = _socket->address.host;
	tosend.address.port = _socket->address.port;
	memcpy(tosend.data, data, size);
	
	SDLNet_UDP_Send(_socket->socket, -1, &tosend);
	
	test t2;
	memcpy(&t2, tosend.data, sizeof(t2));
	
	printf("MAIN packet of type %d \"test\"\n\t: t.type = %d \n\t: test.i = %0.2f \n\t: test.j = %0.2f \n\t: test.w = %f\n", strlen(tosend.data), t2.TYPE, t2.i, t2.j, t2.w);
}
