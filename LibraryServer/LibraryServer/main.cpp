#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include "BookData.h"
#include "ClientReceive.h"
void ErrorHandling(const char* errorMessage);

int main() {
	BookData bookData;
	ClientReceive receiveMsg;
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;

	int szClntAddr;
	char message[500];
	int strLen;
	//�ܼ�â ����
	system("tiTle ����");

	if (WSAStartup(MAKEWORD(2, 2), &wsaData)!=0) {
		ErrorHandling("WSAStartup() error");
	}

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET) {
		ErrorHandling("socket() error");
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(10000);

	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		ErrorHandling("bind() error");
	}

	if (listen(hServSock, 5) == SOCKET_ERROR) {
		ErrorHandling("listen() error");
	}
	szClntAddr = sizeof(clntAddr);
	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
	if (hClntSock == INVALID_SOCKET) {
		ErrorHandling("connect() error");
	}
	strLen = recv(hClntSock, message, sizeof(message) - 1, 0);

	switch (receiveMsg.GetCode(message))
	{
	case 1: {
		//���� ��� ������
		char* str= bookData.SendBookList();
		int length = strlen(str)+1;
		send(hClntSock, str, length, 0);
		free(str);
		//������ ���� ��ȣ �ޱ�
		memset(message, 0, sizeof(message));
		strLen = recv(hClntSock, message, sizeof(message) - 1, 0);
		if (strLen == -1) {
			ErrorHandling("recv() error");
		}
		else {
			receiveMsg.PrintList(message);
		}
		break; 
	}
	case 2:
		break;
	case 3:
		break;
	default:
		printf("GetCode() Error");
		break;
	}
	closesocket(hClntSock);
	closesocket(hServSock);
	WSACleanup();

	system("pause");
	return 0;
}

void ErrorHandling(const char * errorMessage)
{
	fputs(errorMessage, stderr);
	fputc('\n', stderr);
	exit(1);
}
