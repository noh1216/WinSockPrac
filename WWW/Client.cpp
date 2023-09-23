#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include "WinSockErrorModule.h"

#define SERVERIP "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE 251

int main() {
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		return 0;
	}
	SOCKET client_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (client_sock == INVALID_SOCKET) cout << "socket()" << endl;

	//connedt()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(client_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) cout <<"connect()" << endl;
	cout << retval << endl;

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
		strncpy_s(buf, testdata[i], len); // *버퍼에 오버플로우 내보기 -> 런타임 에러남;;

		// 고정길이 데이터 보내기
		retval = send(client_sock, (char*)&len, sizeof(int), 0);
		if (retval == SOCKET_ERROR) {
			cout << "send()" << endl;
			break;
		}

		// 가변길이 데이터 보내기
		retval = send(client_sock, buf, len, 0);
		if (retval == SOCKET_ERROR) {
			cout << "send()" << endl;
			break;
		}
		// 보낸 매세지 처리
		cout << "[TCP 클라이언트] " << 
			sizeof(int) << "+" << retval << "바이트를 보냈습니다" << endl;
	}


	// 윈속 종료
	closesocket(client_sock);
	WSACleanup();


	return 0;
	
}