#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <Windows.h>

#pragma comment(lib, "Ws2_32.lib")

#define SERVERIP "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE 512

using namespace std;

int recvn(SOCKET s, char* buf, int len, int flag) {
	int received;
	char* ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flag);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		if (received == 0)
			break;
		left -= received;
		ptr += received;
	}
}

int main() {

	string id;
	cout << "사용자 아이디를 입력하세요 : ";
	cin >> id;

	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		return 0;
	}
	SOCKET client_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (client_sock == INVALID_SOCKET) cout << "socket()" << endl;

	//connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(client_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) cout << "connect()" << endl;

	Sleep(500);
	cout << "connected to server!" << endl;

	char buf[BUFSIZE];
	while (1) {
		ZeroMemory(&buf, BUFSIZE);
		cout << ""
	}

	closesocket(client_sock);
	WSACleanup();

	return 0;
}