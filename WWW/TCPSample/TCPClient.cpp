/*
	�����͸� �۽��ϰ� �ٽ� �޴´�
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

	// ���� �ʱ�ȭ
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

	// ������ ��ſ� ����� ����
	char buf[BUFSIZE + 1];
	int len;

	// ������ ���
	while (1) {
		cout << endl << "[����������]:";
		cin >> buf;
		/*if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
			break;*/


		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		// �����ͺ����� 
		retval = send(client_sock, buf, len, 0);
		if (retval == SOCKET_ERROR) {
			cout << "send()" << endl;
			break;
		}
		cout << "[TCP Ŭ���̾�Ʈ] " << retval << "����Ʈ�� ���½��ϴ�" << endl;

		// ������ �ޱ�
		retval = recv(client_sock, buf, retval, 0);
		if (retval == SOCKET_ERROR) {
			cout << "recv()" << endl;
			break;
		}

		// ���� ������ ���
		buf[retval] = '\0';
		cout << "[TCP Ŭ���̾�Ʈ] " << retval << "����Ʈ�� �޾ҽ��ϴ�" << endl;
		cout << "[����������] " << buf << endl;
	}



	// ���� ����
	closesocket(client_sock);
	WSACleanup();


	return 0;
	
}