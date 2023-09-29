/*
	�б� ������� ���� �����带 �̺�Ʈ�� ���� ����ȭ
*/

#include <Windows.h>
#include<iostream>

using namespace std;

#define BUFSIZE 10

HANDLE hReadEvent;
HANDLE hWriteEvent;
int buf[BUFSIZE];

// ���� ������
DWORD WINAPI WriteThread(LPVOID arg) {
	DWORD retval;
	for (int i = 1; i <= 500; i++) {
		// �б� �Ϸ� ���
		retval = WaitForSingleObject(hReadEvent, INFINITE);
		if (retval != WAIT_OBJECT_0) break;

		// �������ۿ� ����
		for (int k = 0; k < BUFSIZE; k++) {
			buf[k] = i;
		}

		// ���� �Ϸ� �˸�
		SetEvent(hWriteEvent);
	}
	return 0;
}

DWORD WINAPI ReadThread(LPVOID arg) {
	DWORD retval;

	char* name = (char*)arg;

	while (1) {
		// ���� �Ϸ� ���
		retval = WaitForSingleObject(hWriteEvent, INFINITE);
		if (retval != WAIT_OBJECT_0) break;

		// ���� ������ ���
		cout << "Thread " << GetCurrentThreadId() << "(" << name << "):";
		for (int i = 0; i < BUFSIZE; i++) {
			cout << buf[i] << " ";
		}
		cout << endl;

		// ���� �ʱ�ȭ
		ZeroMemory(&buf, BUFSIZE);

		// �б�Ϸ� �˸�
		SetEvent(hReadEvent);
	}
	return 0;
}


int main() {
	
	// �ڵ����� �̺�Ʈ �ΰ� ����(���ȣ, ��ȣ ����)
	hWriteEvent = CreateEvent(NULL, false, false, NULL);
	if (hWriteEvent == NULL) return 1;
	hReadEvent = CreateEvent(NULL, false, true, NULL);
	if (hReadEvent == NULL) return 1;

	// ������ ����
	HANDLE hThread[3];
	hThread[0] = CreateThread(NULL, 0, WriteThread, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, ReadThread, "Read1", 0, NULL);
	hThread[2] = CreateThread(NULL, 0, ReadThread, "Read2", 0, NULL);

	// ������ ���� ���
	WaitForMultipleObjects(3, hThread, true, INFINITE);

	// �̺�Ʈ ����
	CloseHandle(hWriteEvent);
	CloseHandle(hReadEvent);

	return 0;
}