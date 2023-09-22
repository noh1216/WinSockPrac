#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

// WinSock Libaray
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

void err_quit(const char* msg);
void err_display(const char* msg);