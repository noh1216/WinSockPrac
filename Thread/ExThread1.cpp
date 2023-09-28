/*
	== ����������� �帧�� �˱����� ���� �ڵ� == 
	
	x,y,z���� ������ Point3D ����ü ������ �����忡 �� ����
	MyThread�� 1�ʿ� �ѹ��� ���μ��� ���̵�� pt���� ������ش�.
	
	main �Լ��� ���μ��� ���̵� ���
*/

#include <iostream>
#include <Windows.h>

using namespace std;

struct Point3D {
	int x, y, z;
};

DWORD WINAPI myThread(LPVOID arg) {
	Point3D* pt = (Point3D*)arg;
	for(int i=0;i < 10; i++) {
		cout << "Running Thread() " << GetCurrentProcessId() << ":" <<
			pt->x << ", " << pt->y << ", " << pt->z << endl;
		Sleep(1000);
	}
	delete pt;
	return 0;
}

int main() {
	Point3D* pt = new Point3D[2];

	// first Thread
	pt[0].x = 10; pt[0].y = 20; pt[0].z = 30;
	HANDLE hThread1 = CreateThread(NULL, 0, myThread, &pt[0], 0,NULL);
	if (hThread1 == NULL) return 1;
	CloseHandle(hThread1);

	// Second Thread
	pt[1].x = 40; pt[1].y = 50; pt[1].z = 60;
	HANDLE hThread2 = CreateThread(NULL, 0, myThread, &pt[1], 0, NULL);
	if (hThread2 == NULL) return 1;
	CloseHandle(hThread2);

	for (int i = 0; i < 10; i++) {
		cout << "Running main() " << GetCurrentProcessId() << endl;
		Sleep(1000);
	}

	return 0;
}