#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include "WinSockErrorModule.h"

#define SERVERIP "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE 512

int main() {
	int retval;

	// ���� �ʱ�ȭ
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


	// ������ ��ſ� ����� ����
	char buf[BUFSIZE];
	char* testdata[] = {
		"�̸� : ������",
		"��� : ��� ��û",
		"�����ϴ°� : �θǽ� ���(���״�&��Ƽ�λ��̵� �����ϴ� ��)",
		"������ ����ģ�� : 19��, �Ѵ޻��"
	};
	int len;

	//���� ������ ���
	for (int i = 0; i < 4; i++) {
		//������ �Է� 
		len = strlen(testdata[i]);
		strncpy(buf, testdata[i], len); // *���ۿ� �����÷ο� ������

		// �������� ������ ������
		
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			break;
		}

		// �������� ������ ������

		if (retval == SOCKET_ERROR) {
			err_display("send()");
			break;
		}

	}
	// ���� �ż��� ó��


	// ���� ����

	return 0;
	
}