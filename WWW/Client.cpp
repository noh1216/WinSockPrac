#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include "WinSockErrorModule.h"

#define SERVERIP "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE 251

int main() {
	int retval;

	// ���� �ʱ�ȭ
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
		strncpy_s(buf, testdata[i], len); // *���ۿ� �����÷ο� ������ -> ��Ÿ�� ������;;

		// �������� ������ ������
		retval = send(client_sock, (char*)&len, sizeof(int), 0);
		if (retval == SOCKET_ERROR) {
			cout << "send()" << endl;
			break;
		}

		// �������� ������ ������
		retval = send(client_sock, buf, len, 0);
		if (retval == SOCKET_ERROR) {
			cout << "send()" << endl;
			break;
		}
		// ���� �ż��� ó��
		cout << "[TCP Ŭ���̾�Ʈ] " << 
			sizeof(int) << "+" << retval << "����Ʈ�� ���½��ϴ�" << endl;
	}


	// ���� ����
	closesocket(client_sock);
	WSACleanup();


	return 0;
	
}