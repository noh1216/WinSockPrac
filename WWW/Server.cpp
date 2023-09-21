#include <iostream>
#include <stdlib.h>
#include <stdio.h>

// WinSock Libaray
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define SERVERPORT 9000
#define BUFSIZE 512

using namespace std;

int main() {
	int retval;

	// WinSock initalization
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		return 0;
	}

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) cout << "socket()" << endl;

	// bind()
	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htonl(SERVERPORT);
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(listen_sock, (SOCKADDR*)&sockaddr, sizeof(sockaddr));
	if (retval == SOCKET_ERROR) cout << "bind()" << endl;

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) cout << "listen()" << endl;

	// Data using variables
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE+1];
	int len;

	// Closesocket()
	closesocket(listen_sock);

	// WinSock Exit
	WSACleanup();

	return 0;
}