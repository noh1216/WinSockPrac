/*
	1~100���� ���� ���ϸ鼭 ������ ����ȭ�� �˾ƺ��� �ڵ�

	WaitForSingleObject (������ �ڵ�, ���ð�)
	@return : WAIT_OBJECT_0 - ������ ��������
			  WAIT_TIMEOUT - �ð��ȿ� �����尡 �������� ����
			  WAIT_FAILED - ����
*/

#include <Windows.h>
#include<iostream>

using namespace std;

int sum = 0;

DWORD WINAPI MyThread(LPVOID arg) {
	int num = (int)arg;
	for (int i = 1; i <= num; i++) {
		sum += i;
	}
	return 0;
}

int main() {
	int num = 5000000;
	HANDLE hThread = CreateThread(NULL, 0, MyThread, (LPVOID)num, CREATE_SUSPENDED, NULL);
	if (hThread == NULL) return 1;

	cout << "������ ������. ����� : " << sum << endl;
	ResumeThread(hThread);
	if (WaitForSingleObject(hThread, 1) == WAIT_TIMEOUT) {
		cout << "**" << endl;
	}
	cout << "������ ������. ����� : " << sum << endl;
	CloseHandle(hThread);

	return 0;
}