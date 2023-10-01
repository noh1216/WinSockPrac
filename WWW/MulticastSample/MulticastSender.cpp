#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include <iostream>

// WinSock Libaray
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define MULTICASTIP "235.7.8.9"
#define REMOTEPORT 9000
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

	// 멀티캐스트 TTL 설정
	int ttl = 2;
	retval = setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&ttl, sizeof(ttl));
	if (retval == SOCKET_ERROR) return 1;

	// 소켓 구조체 초기화
	SOCKADDR_IN remoteaddr;
	ZeroMemory(&remoteaddr, sizeof(remoteaddr));
	remoteaddr.sin_family = AF_INET;
	remoteaddr.sin_addr.s_addr = inet_addr(MULTICASTIP);
	remoteaddr.sin_port = htons(REMOTEPORT);

	char buf[BUFSIZE + 1];
	int len;

	while (1) {
		// 데이터 입력 
		cout << "[보낼 데이터] ";
		cin >> buf;

		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		// 데이터 보내기
		retval = sendto(sock, buf, strlen(buf), 0, (SOCKADDR*)&remoteaddr, sizeof(remoteaddr));
		if (retval == SOCKET_ERROR) {
			cout << "sendto()" << endl;
			continue;
		}
		cout << "[UDP] " << retval << "바이트를 보냈습니다." << endl;
	}

	//	closesocket()
	closesocket(sock);

	// exit winsock
	WSACleanup();
	return 0;
}