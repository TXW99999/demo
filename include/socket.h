#pragma  once

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") 
#include <stdio.h>

#if defined(__cplusplus)
extern "C" {
#endif
#define  UDP_LENGTH 59
	SOCKET socket_create();
	int socket_bind(SOCKET socket, int port);
	int socket_send(SOCKET socket, char* ip, int nPort, char* pData);
	int socket_recv(SOCKET socket, char* buff, sockaddr_in& client);
	int socket_over(SOCKET socket);

#if defined(__cplusplus)
}
#endif
