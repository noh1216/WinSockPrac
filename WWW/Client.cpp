/*
	데이터를 송신하고 다시 받는다
*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS 


#include <iostream>
#include <stdlib.h>
#include <stdio.h>

// WinSock Libaray
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include <Windows.h>

#define SERVERIP "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE 251

using namespace std;

int main() {
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
	if (retval == SOCKET_ERROR) cout <<"connect()" << endl;

	// 데이터 통신에 사용할 변수
	char buf[BUFSIZE + 1];
	int len;

	// 서버랑 통신
	while (1) {
		cout << endl << "[보낼데이터]:";
		cin >> buf;
		/*if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
			break;*/


		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		// 데이터보내기 
		retval = send(client_sock, buf, len, 0);
		if (retval == SOCKET_ERROR) {
			cout << "send()" << endl;
			break;
		}
		cout << "[TCP 클라이언트] " << retval << "바이트를 보냈습니다" << endl;

		// 데이터 받기
		retval = recv(client_sock, buf, retval, 0);
		if (retval == SOCKET_ERROR) {
			cout << "recv()" << endl;
			break;
		}

		// 받은 데이터 출력
		buf[retval] = '\0';
		cout << "[TCP 클라이언트] " << retval << "바이트를 받았습니다" << endl;
		cout << "[받은데이터] " << buf << endl;
	}



	// 윈속 종료
	closesocket(client_sock);
	WSACleanup();


	return 0;
	
}