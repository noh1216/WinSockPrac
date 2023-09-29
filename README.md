# WinSockPrac"

내맘대로 만든 윈속 연습용파일 

## WinSock 파일설명 (Update 2023.09.26)

### Project
> - **winsock_basic** : Microsoft에서 제공해주는 설명으로 버퍼를 받는 서버&클라이언트 구현 (기본 구성)
> - **WWW** : 내 방식대로 만든 윈속 기초 파일
> - **clientPrac** : 클라이언트 코드 연습파일 
> - **MultiThreadServer** : 멀티스레드 서버 구현
> - **Thread** : 스레드 연습용
> - _**ErrorModules** : (번외) 에러 출력 코드포함_



* * *

### WWW
> - [x] Client.cpp : 데이터를 서버에 보내고(send) 다시 받는(recv)코드
> - [x] Server.cpp : recvn()으로 고정+가변 데이터를 받는 파일.. 이었으나 복사를 안하고 쓰는 바람에 멀티스레드 파일이 되어버림;;


### MultiThreadServer
> - [x] MultiThreadServer.cpp : 멀티스레드를 이용한 서버 데이터를 받고(send) 다시 돌려주는(recv) 코드 [+WWW/Server.cpp와 동일]

<<<<<<< HEAD
### clientPrac 
> - [ ] TCPClient_chat_practice1.cpp : 클라이언트와 데이터를 주고 받는 서버 프로그램을 작성하려 헀으나 				
귀차니즘과 훈련 이슈로 터치 못하는 중(추후에 멀티스레드 이용해서 채팅프로그램으로 만들예정)

### Thread 
> - [x] ExThread1 : 스레드 생성, 구조체인자 동적할당 후 전달
=======
### WinSockPrac 
> WinsockChatting : 클라이언트와 데이터를 주고 받는 서버 프로그램을 작성하려 헀으나 				
					귀차니즘과 훈련 이슈로 터치 못하는 중(추후에 멀티스레드 이용해서 채팅프로그램으로 만들예정)
> > - [ ] TCPClient_chat_practice1.cpp : 고정+가변 형식 데이터 송수신
> > - [ ] TCPClient_chat_practice1.cpp : 고정+가변 형식 데이터 송수신
>>>>>>> server_prac
