/*
	sockaddr���� ��Ʈ �����ý� ����Ʈ ���� �Լ� ntohs�� ������
	�ؿ��ִ� #define _WINSOCK_DEPRECATED_NO_WARNINGS �� ����ϰų� 
	inet_ntoa() ��� inet_ntop() or InetNtop() �� ���
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS 

//#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
//
//// WinSock Libaray
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#pragma comment(lib, "ws2_32.lib")

// User Define function
#include "WinSockErrorModule.h"

#define SERVERPORT 9000
#define BUFSIZE 512

using namespace std;


// User Define Data receive function
int recvn(SOCKET s, char* buf, int len, int flags) {
	int received;
	char* ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}

int main() {
	int retval;

	// WinSock initalization
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		return 0;
	}

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(SERVERPORT);
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(listen_sock, (SOCKADDR*)&sockaddr, sizeof(sockaddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// Data communication variables
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE+1];
	int len;

	while (1) {
		//accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}

		// ������ Ŭ���̾�Ʈ ����
		cout << endl << "[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ�=" << inet_ntoa(clientaddr.sin_addr)
			<< ", ��Ʈ=" << ntohs(clientaddr.sin_port) << endl; // *����Ʈ���� ������!

		while (1) {
			// �������� ������ �ޱ�
			retval = recvn(client_sock, (char*)&len, sizeof(int), 0); // ������ ���� ���� ����
			if (retval == SOCKET_ERROR) {
				err_display("recvn()");
				break;
			}
			else if (retval == 0)
				break;

			// �������� ������ �ޱ�
			retval = recvn(client_sock, buf, len, 0);
			if (retval == SOCKET_ERROR) {
				err_display("reccv()");
			}
			else if (retval == 0)
				break;

			// ���� ������ ���
			buf[retval] = '\0'; // ù��° �ڸ� �ʱ�ȭ
			cout << "[TCP/" << inet_ntoa(clientaddr.sin_addr) << ":" << ntohs(clientaddr.sin_port) << "]" << buf << endl;


		}
		//closesocket()
		closesocket(client_sock);
		cout << "[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=" << inet_ntoa(clientaddr.sin_addr) << 
			", ��Ʈ=" << ntohs(clientaddr.sin_port) << endl;

	}

	// Closesocket()
	closesocket(listen_sock);

	// WinSock Exit
	WSACleanup();

	return 0;
}