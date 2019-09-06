#include "ServerReceive.h"



ServerReceive::ServerReceive()
{
}


ServerReceive::~ServerReceive()
{
}

void ServerReceive::PrintList(const char str[])
{
	Document d;
	d.Parse(str);
	int i = 0;
	printf("===================\n");
	for (auto& book : d.GetArray()) {
		printf("��ȣ : %d\n", book["id"].GetInt());
		printf("���� : %s\n", book["name"].GetString());
		printf("���� : %s", book["writer"].GetString());
		if (book["translator"].IsNull()) {
			printf("\n");
		}
		else {
			printf("|���� : %s\n", book["translator"].GetString());
		}
		printf("���ǻ� : %s\n", book["publisher"].GetString());
		printf("���� : %d\n", book["cost"].GetInt());
		if (book["lend"].GetBool()) {
			printf("�뿩��");
		}
		
		printf("===================\n");
	}
}
