#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include <iostream>

// WinSock Libaray
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#define MULTICASTIP "235.7.8.9"
#define LOCALPORT 9000
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
	if (sock == INVALID_SOCKET) return 1;

	// SO_REUSEADDR 옵션 설정
	bool optval = true;
	retval = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval));

	// bind()
	SOCKADDR_IN localaddr;
	ZeroMemory(&localaddr, sizeof(localaddr));
	localaddr.sin_family = AF_INET;
	localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localaddr.sin_port = htons(LOCALPORT);
	retval = bind(sock, (SOCKADDR*)&localaddr, sizeof(localaddr));
	if (retval == SOCKET_ERROR) return 1;

	// 멀티캐스트 그룹가입
	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr = inet_addr(MULTICASTIP);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	retval = setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq));
	if (retval == SOCKET_ERROR) return 1;

	SOCKADDR_IN peeraddr;
	int addrlen;
	char buf[BUFSIZE+1];

	// 브로드캐스트 데이터 받기
	while (1) {
		// 데이터 받기 
		addrlen = sizeof(peeraddr);
		retval = recvfrom(sock, buf, BUFSIZE, 0, (SOCKADDR*)&peeraddr, &addrlen);
		if (retval == SOCKET_ERROR) {
			cout << "recvfrom()" << endl;
			continue;
		}

		// 받은데이터 출력
		buf[retval] = '\0';
		cout << "[UDP/" << inet_ntoa(peeraddr.sin_addr) << ":" << ntohs(peeraddr.sin_port) << "] " << buf << endl;
	}

	// 멀티캐스트 그룹 탈퇴
	retval = setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&mreq, sizeof(mreq));
	if (retval == SOCKET_ERROR) return 1;

	// closesocket()
	closesocket(sock);

	WSACleanup();
	return 0;
}
