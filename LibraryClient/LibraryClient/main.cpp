#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include "ClientSend.h"
#include "ServerReceive.h"
void ErrorHandlig(const char* errorMessage);

int main() {
	ClientSend sendMsg;
	ServerReceive recvMsg;

	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char message[500];
	int strLen;

	//콘솔창 제목 및 색상 지정
	system("tiTle 도서관리");
	system("cOLoR f0");

	if (WSAStartup(MAKEWORD(2, 2), &wsaData)!=0) {
		ErrorHandlig("WSAStartup() error");
	}

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET) {
		ErrorHandlig("socket() error");
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(10000);

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		ErrorHandlig("connect() error");
	}
	int cho = 0;
	while (cho!=3) {
		bool retry = false;
		printf("1) 도서 대출 2)도서 반납 3)끝내기 : ");
		scanf_s("%d", &cho);//예외처리!
		switch (cho) {
		case 1:
		{//도서목록 요청
			char* str = sendMsg.RequestBookList();
			int length = strlen(str)+1;
			send(hSocket, str, length, 0);
			free(str);
			//도서목록 받고 출력
			strLen = recv(hSocket, message, sizeof(message) - 1, 0);
			if (strLen == -1) {
				ErrorHandlig("recv() error");
			}
			else {
				recvMsg.PrintList(message);
			}
			printf("대출할 도서의 id를 입력해주세요!\n");
			//대출할 도서 번호 보내기
			int borrow = 0;
			printf("->");
			scanf_s("%d", &borrow);
			str = sendMsg.BorrowBook(borrow);
			length = strlen(str) + 1;
			send(hSocket, str, length, 0);
			free(str);
			
			//대출 결과 받기
			memset(message, 0, sizeof(message));
			strLen = recv(hSocket, message, sizeof(message) - 1, 0);
			recvMsg.BrrResult(message);
			break; 
		}
		case 2:
		{
			if (recvMsg.CheckCanReturn()) {
				recvMsg.PrintBrrList();
				printf("반납할 도서의 id를 입력해주세요!\n");
				//반납할 도서 번호 보내기
				int ret = 0;
				printf("->");
				scanf_s("%d", &ret);
				if (recvMsg.CheckBrrBookID(ret)) {
					char* str = sendMsg.ReturnBook(ret);
					int length = strlen(str) + 1;
					send(hSocket, str, length, 0);
					free(str);

					//반납 결과 받기
					memset(message, 0, sizeof(message));
					strLen = recv(hSocket, message, sizeof(message) - 1, 0);
					recvMsg.ReturnResult(message);
				}
			}
			break; 
		}
		case 3:
		{
			char* str = sendMsg.RequestBookList();
			int length = strlen(str) + 1;
			send(hSocket, str, length, 0);
			free(str);
			retry = true;
			printf("도서 관리 프로그램을 종료합니다\n");
			break; 
		}
		default:
			retry = true;
			printf("잘못된 입력입니다! 1~3까지의 숫자를 입력해주시기 바랍니다.\n");
			break;
		}
		if (retry == true) {
			continue;
		}
		cho = 0;
	}
	closesocket(hSocket);
	WSACleanup();
	system("pause");
	return 0;
}
void ErrorHandlig(const char * errorMessage)
{
	fputs(errorMessage, stderr);
	fputc('\n', stderr);
	exit(1);
}
