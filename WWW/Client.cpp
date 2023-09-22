#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include "WinSockErrorModule.h"

#define SERVERIP "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE 512

int main() {
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		return 0;
	}
	SOCKET client_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (client_sock == INVALID_SOCKET) err_quit("socket()");

	//connedt()
	sockaddr_in sockaddr;
	ZeroMemory(&sockaddr, sizeof(sockaddr));
	sockaddr.sin_addr.s_addr = inet_addr(SERVERIP);
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(SERVERPORT);
	retval = connect(client_sock, (sockaddr_in*)&sockaddr, sizeof(sockaddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");


	// 데이터 통신에 사용할 변수
	char buf[BUFSIZE];
	char* testdata[] = {
		"이름 : 양종민",
		"취미 : 드라마 시청",
		"좋아하는것 : 로맨스 드라마(별그대&뷰티인사이드 좋아하는 편)",
		"마지막 여자친구 : 19살, 한달사귐"
	};
	int len;

	//서버 데이터 통신
	for (int i = 0; i < 4; i++) {
		//데이터 입력 
		len = strlen(testdata[i]);
		strncpy(buf, testdata[i], len); // *버퍼에 오버플로우 내보기

		// 고정길이 데이터 보내기
		
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			break;
		}

		// 가변길이 데이터 보내기

		if (retval == SOCKET_ERROR) {
			err_display("send()");
			break;
		}

	}
	// 보낸 매세지 처리


	// 윈속 종료

	return 0;
	
}