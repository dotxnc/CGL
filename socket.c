#include "socket.h"

void cgl_InitSocket(Socket* _socket, const char* ip, int port, CGL_SOCKET_TYPE type)
{
	if (init_sdl_net) SDLNet_Init();
	
	_socket->type = type;
	
	if (type == CGL_SERVER) {
		printf("SERVER STARTED\n");
		_socket->socket = SDLNet_UDP_Open(port);
		SDLNet_ResolveHost(&_socket->address, NULL, port);
	}
	else if (type == CGL_CLIENT) {
		_socket->socket = SDLNet_UDP_Open(0);
		SDLNet_ResolveHost(&_socket->address, ip, port);
	}
	
	if (_socket->socket == NULL) {
		printf("Socket not created, %d, %s\n", type, SDLNet_GetError());
		return;
	}
	_socket->numclients = 0;
	_socket->packet = SDLNet_AllocPacket(256);
	
	if (type == CGL_CLIENT)
	{
		_cgl_connection connection = {CGL_CONNECTION, CGL_CONNECT};
		cgl_SendSocket(_socket, &connection, sizeof(_cgl_connection));
	}
}

void cgl_UpdateSocket(Socket* _socket)
{
	
	if (_socket == NULL) return;
	if (SDLNet_UDP_Recv(_socket->socket, _socket->packet))
	{
		if (_socket->type == CGL_SERVER)
		{
			BYTE* data = (BYTE*)malloc(_socket->packet->len);
			memcpy(data, _socket->packet->data, _socket->packet->len);
			int type = abs(data[0]);
			
			switch (type)
			{
			case CGL_CONNECTION: {
				_cgl_connection packet;
				memcpy(&packet, _socket->packet->data, sizeof(_cgl_connection));
				switch (packet.data)
				{
				case CGL_CONNECT: {
					
					Client client;
					client.id = _socket->numclients + 1;
					client.addr = _socket->packet->address;
					_socket->clients[_socket->numclients] = client;
					_socket->numclients++;
					
					unsigned int  addr = _socket->packet->address.host;
					BYTE octet[4]  = {0,0,0,0};
					for (int i=0; i<4; i++)
						octet[i] = ( addr >> (i*8) ) & 0xFF;
					
					printf("SERV: new client with id %d connected from %d.%d.%d.%d:%d\n", client.id, octet[0], octet[1], octet[2], octet[3], _socket->packet->address.port);
					
					for (int i = 0; i < _socket->numclients; i++) {
						if (_socket->clients[i].id != client.id) { // send to all clients except new one
							_cgl_clientdata cdata = {CGL_CLIENTDATA, client.id};
							cgl_SendToClientSocket(_socket, _socket->clients[i].addr, &cdata, sizeof(_cgl_clientdata));
							
							cdata.id = _socket->clients[i].id;
							cgl_SendToClientSocket(_socket, _socket->clients[client.id-1].addr, &cdata, sizeof(_cgl_clientdata));
						}
					}
					
					_cgl_clientdata localid = {CGL_LOCALID, client.id};
					cgl_SendToClientSocket(_socket, client.addr, &localid, sizeof(_cgl_clientdata));
					
					BYTE* test = (BYTE*)malloc(sizeof(localid));
					memcpy(test, &localid, sizeof(localid));
					
					_cgl_clientdata ucomp;
					memcpy(&ucomp, test, sizeof(ucomp));
					
					if (_socket->callback_conn!=NULL)
						_socket->callback_conn(_socket, client.id);
					
				} break;
				case CGL_DISCONNECT: {
				
				} break;
				default:
					break;
				}
			} break;
			default:
				if (_socket->callback_recv!=NULL)
					_socket->callback_recv(_socket, _socket->packet);
				break;
			}
			
			if (_socket->callback_recv!=NULL)
				_socket->callback_recv(_socket, _socket->packet);
		}
		else if (_socket->type == CGL_CLIENT)
		{
			
			BYTE* data = (BYTE*)malloc(_socket->packet->len);
			memcpy(data, _socket->packet->data, _socket->packet->len);
			int type = abs(data[0]);
			
			switch (type)
			{
			case CGL_LOCALID: {
				_cgl_clientdata packet;
				memcpy(&packet, data, sizeof(_cgl_clientdata));
				_socket->localID = packet.id;
				printf("CLI: local id: %d\n", packet.id);
			} break;
			case CGL_CLIENTDATA: {
				_cgl_clientdata packet;
				memcpy(&packet, data, sizeof(_cgl_clientdata));
				printf("CLI: got new client with id %d\n", packet.id);
				
				Client client;
				client.id = packet.id;
				_socket->clients[_socket->numclients] = client;
				_socket->numclients++;
				
				if (_socket->callback_conn!=NULL)
					_socket->callback_conn(_socket, client.id);
				
			} break;
			default:
				if (_socket->callback_recv!=NULL)
					_socket->callback_recv(_socket, _socket->packet);
				break;
			}
			
			// printf("CLI: received data\n");
			if (_socket->callback_recv!=NULL)
				_socket->callback_recv(_socket, _socket->packet);
		}
	}
}

void cgl_SendSocket(Socket* _socket, void* data, unsigned int size)
{
	// BYTE* buffer = (BYTE*)malloc(size);
	BYTE buffer[size];
	memcpy(buffer, data, size);
	
	int *fuck = (int*)malloc(sizeof(int));
	fuck = (int*)5;
	printf("%d  %d  %d  %d %d\n", size, sizeof(buffer), sizeof(data), strlen(buffer), fuck);
	
	_socket->packet->len = sizeof(buffer);
	_socket->packet->data = (Uint8*)malloc(sizeof(buffer));
	_socket->packet->address.host = _socket->address.host;
	_socket->packet->address.port = _socket->address.port;
	memcpy(_socket->packet->data, data, sizeof(buffer));
	
	SDLNet_UDP_Send(_socket->socket, -1, _socket->packet);
	
}

void cgl_SendToClientSocket(Socket* _socket, IPaddress to, void* data, unsigned int size)
{
	// printf("CGL: sending packeting with size of %d\n", size);
	// BYTE* buffer = (BYTE*)malloc(size);
	BYTE buffer[size];
	memcpy(buffer, data, size);
	// strcat((char)1, buffer);
	
	UDPpacket tosend;
	tosend.len = sizeof(buffer);
	tosend.data = (Uint8*)malloc(sizeof(buffer));
	tosend.address.host = to.host;
	tosend.address.port = to.port;
	memcpy(tosend.data, buffer, sizeof(buffer));
	
	SDLNet_UDP_Send(_socket->socket, -1, &tosend);
}

void cgl_SetCallbackSocket(Socket* _socket, const void* recv, const void* conn, const void* dconn)
{
	_socket->callback_recv = recv;
	_socket->callback_conn = conn;
	_socket->callback_dconn = dconn;
}

Client cgl_GetClientSocket(Socket* _socket, int id)
{
	for (int i = 0; i < _socket->numclients; i++)
		if (_socket->clients[i].id == id)
			return _socket->clients[i];
}
