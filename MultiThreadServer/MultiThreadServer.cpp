/*
	serveraddr���� ��Ʈ �����ý� ����Ʈ ���� �Լ� ntohs�� ������
	�ؿ��ִ� #define _WINSOCK_DEPRECATED_NO_WARNINGS �� ����ϰų� 
	inet_ntoa() ��� inet_ntop() or InetNtop() �� ���

	Windows.h ���� winsock2.h ���� �� ��
	Windows.h�� ������ winsock.h�� �־ �浹��
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

#define SERVERPORT 9000
#define BUFSIZE 512

using namespace std;

DWORD WINAPI ProcessClient(LPVOID arg) {
	SOCKET client_sock = (SOCKET)arg;
	int retval;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE+1];

	// Ŭ���̾�Ʈ ���� ���
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (sockaddr*)&clientaddr, &addrlen);

	while (1) {
		retval = recv(client_sock, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			cout << "recv()" << endl;
			break;
		}
		else if (retval == 0)
			break;

		buf[retval] = '\0';
		cout << "[TCP/" << inet_ntoa(clientaddr.sin_addr) << ":" 
			<< ntohs(clientaddr.sin_port) <<"] " << buf << endl;

		retval = send(client_sock, buf, retval, 0);
		if (retval == SOCKET_ERROR) {
			cout << "send()" << endl;
			break;
		}
	}

	// closesocket
	closesocket(client_sock);
	cout << "[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=" 
		<< inet_ntoa(clientaddr.sin_addr) <<
		", ��Ʈ=" << ntohs(clientaddr.sin_port) << endl;
	return 0;
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
	if (listen_sock == INVALID_SOCKET) cout << "socket()" << endl;

	// bind()
	sockaddr_in serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVERPORT);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) cout << "bind()" << endl;

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) cout << "listen()" << endl;

	// Data communication variables
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE+1];
	int len;
	HANDLE hThread;

	while (1) {
		//accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			cout << "accept()" << endl;
			break;
		}

		// ������ Ŭ���̾�Ʈ ����
		cout << endl << "[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ�=" << inet_ntoa(clientaddr.sin_addr)
			<< ", ��Ʈ=" << ntohs(clientaddr.sin_port) << endl; 

		// ������ ����
		hThread = CreateThread(NULL, 0, ProcessClient, (LPVOID)client_sock, 0, NULL);
		if (hThread == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread); }
	}

	// Closesocket()
	closesocket(listen_sock);

	// WinSock Exit
	WSACleanup();

	return 0;
}