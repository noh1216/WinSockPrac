#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include <iostream>

// WinSock Libaray
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define LOCALPORT 9000
#define BUFSIZE 512

using namespace std;

int main() {
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) return 1;

	// bind()
	SOCKADDR_IN localaddr;
	ZeroMemory(&localaddr, sizeof(localaddr));
	localaddr.sin_family = AF_INET;
	localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localaddr.sin_port = htons(LOCALPORT);
	retval = bind(sock, (SOCKADDR*)&localaddr, sizeof(localaddr));
	if (retval == SOCKET_ERROR) return 1;

	SOCKADDR_IN peeraddr;
	int addrlen;
	char buf[BUFSIZE+1];

	// ��ε�ĳ��Ʈ ������ �ޱ�
	while (1) {
		// ������ �ޱ� 
		addrlen = sizeof(peeraddr);
		retval = recvfrom(sock, buf, BUFSIZE, 0, (SOCKADDR*)&peeraddr, &addrlen);
		if (retval == SOCKET_ERROR) {
			cout << "recvfrom()" << endl;
			continue;
		}

		// ���������� ���
		buf[retval] = '\0';
		cout << "[UDP/" << inet_ntoa(peeraddr.sin_addr) << ":" << ntohs(peeraddr.sin_port) << "] " << buf << endl;
	}

	// closesocket()
	closesocket(sock);

	WSACleanup();
	return 0;
}
