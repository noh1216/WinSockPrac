#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include <iostream>

// WinSock Libaray
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define SERVERIP "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE 512

using namespace std;

int main() {
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) cout << "socket()" << endl;

	// 소켓구조체 초기화
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVERPORT);
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);

	SOCKADDR_IN peeraddr;
	int addrlen;
	char buf[BUFSIZE+1];
	int len;

	while (1) {
		cout << "[보낼데이터] ";
		cin >> buf;

		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		// 데이터 보내기
		retval = sendto(sock, buf, strlen(buf), 0, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
		if (retval == SOCKET_ERROR) {
			cout << "sendto()" << endl;
			continue;
		}
		cout << "[UDP 클라이언트] " << retval << "바이트를 보냈습니다." << endl;

		// 데이터 받기
		addrlen = sizeof(peeraddr);
		retval = recvfrom(sock, buf, BUFSIZE, 0,(SOCKADDR*)&peeraddr, &addrlen);
		if (retval == SOCKET_ERROR) {
			cout << "recvfrom()"  << endl;
			continue;
		}

		// 송신자 IP 주소체크
		if (memcmp(&peeraddr, &serveraddr, sizeof(peeraddr))) {
			cout << "[오류] 잘못된 데이터입니다" << endl;
			continue;
		}

		// 받은데이터 출력
		buf[retval] = '\0';
		cout << "[UDP 클라이언트] " << retval << "바이트를 받았습니다." << endl;
		cout << "[받은데이터] " << buf << endl;
	}

	// closesocket()
	closesocket(sock);

	WSACleanup();
	return 0;
}
