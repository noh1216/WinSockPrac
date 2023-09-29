/*
	읽기 스레드와 쓰기 스레드를 이벤트를 통해 동기화
*/

#include <Windows.h>
#include<iostream>

using namespace std;

#define BUFSIZE 10

HANDLE hReadEvent;
HANDLE hWriteEvent;
int buf[BUFSIZE];

// 쓰기 스레드
DWORD WINAPI WriteThread(LPVOID arg) {
	DWORD retval;
	for (int i = 1; i <= 500; i++) {
		// 읽기 완료 대기
		retval = WaitForSingleObject(hReadEvent, INFINITE);
		if (retval != WAIT_OBJECT_0) break;

		// 공유버퍼에 저장
		for (int k = 0; k < BUFSIZE; k++) {
			buf[k] = i;
		}

		// 쓰기 완료 알림
		SetEvent(hWriteEvent);
	}
	return 0;
}

DWORD WINAPI ReadThread(LPVOID arg) {
	DWORD retval;

	char* name = (char*)arg;

	while (1) {
		// 쓰기 완료 대기
		retval = WaitForSingleObject(hWriteEvent, INFINITE);
		if (retval != WAIT_OBJECT_0) break;

		// 읽은 데이터 출력
		cout << "Thread " << GetCurrentThreadId() << "(" << name << "):";
		for (int i = 0; i < BUFSIZE; i++) {
			cout << buf[i] << " ";
		}
		cout << endl;

		// 버퍼 초기화
		ZeroMemory(&buf, BUFSIZE);

		// 읽기완료 알림
		SetEvent(hReadEvent);
	}
	return 0;
}


int main() {
	
	// 자동리셋 이벤트 두개 생성(비신호, 신호 상태)
	hWriteEvent = CreateEvent(NULL, false, false, NULL);
	if (hWriteEvent == NULL) return 1;
	hReadEvent = CreateEvent(NULL, false, true, NULL);
	if (hReadEvent == NULL) return 1;

	// 스레드 생성
	HANDLE hThread[3];
	hThread[0] = CreateThread(NULL, 0, WriteThread, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, ReadThread, "Read1", 0, NULL);
	hThread[2] = CreateThread(NULL, 0, ReadThread, "Read2", 0, NULL);

	// 스레드 종료 대기
	WaitForMultipleObjects(3, hThread, true, INFINITE);

	// 이벤트 제거
	CloseHandle(hWriteEvent);
	CloseHandle(hReadEvent);

	return 0;
}