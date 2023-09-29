/*
	1~100까지 전부 터하면서 스레드 동기화를 알아보는 코드

	WaitForSingleObject (스레드 핸들, 대기시간)
	@return : WAIT_OBJECT_0 - 스레드 정상종료
			  WAIT_TIMEOUT - 시간안에 스레드가 종료하지 않음
			  WAIT_FAILED - 실패
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

	cout << "스레드 실행전. 계산결과 : " << sum << endl;
	ResumeThread(hThread);
	if (WaitForSingleObject(hThread, 1) == WAIT_TIMEOUT) {
		cout << "**" << endl;
	}
	cout << "스레드 실행후. 계산결과 : " << sum << endl;
	CloseHandle(hThread);

	return 0;
}