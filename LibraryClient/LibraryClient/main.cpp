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

	//�ܼ�â ���� �� ���� ����
	system("tiTle ��������");
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
		printf("1) ���� ���� 2)���� �ݳ� 3)������ : ");
		scanf_s("%d", &cho);//����ó��!
		switch (cho) {
		case 1:
		{//������� ��û
			char* str = sendMsg.RequestBookList();
			int length = strlen(str)+1;
			send(hSocket, str, length, 0);
			free(str);
			//������� �ް� ���
			strLen = recv(hSocket, message, sizeof(message) - 1, 0);
			if (strLen == -1) {
				ErrorHandlig("recv() error");
			}
			else {
				recvMsg.PrintList(message);
			}
			printf("������ ������ id�� �Է����ּ���!\n");
			//������ ���� ��ȣ ������
			int borrow = 0;
			printf("->");
			scanf_s("%d", &borrow);
			str = sendMsg.BorrowBook(borrow);
			length = strlen(str) + 1;
			send(hSocket, str, length, 0);
			free(str);
			
			//���� ��� �ޱ�
			memset(message, 0, sizeof(message));
			strLen = recv(hSocket, message, sizeof(message) - 1, 0);
			recvMsg.BrrResult(message);
			break; 
		}
		case 2:
		{
			if (recvMsg.CheckCanReturn()) {
				recvMsg.PrintBrrList();
				printf("�ݳ��� ������ id�� �Է����ּ���!\n");
				//�ݳ��� ���� ��ȣ ������
				int ret = 0;
				printf("->");
				scanf_s("%d", &ret);
				if (recvMsg.CheckBrrBookID(ret)) {
					char* str = sendMsg.ReturnBook(ret);
					int length = strlen(str) + 1;
					send(hSocket, str, length, 0);
					free(str);

					//�ݳ� ��� �ޱ�
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
			printf("���� ���� ���α׷��� �����մϴ�\n");
			break; 
		}
		default:
			retry = true;
			printf("�߸��� �Է��Դϴ�! 1~3������ ���ڸ� �Է����ֽñ� �ٶ��ϴ�.\n");
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
