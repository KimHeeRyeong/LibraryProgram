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
		printf("번호 : %d\n", book["id"].GetInt());
		printf("제목 : %s\n", book["name"].GetString());
		printf("저자 : %s", book["writer"].GetString());
		if (book["translator"].IsNull()) {
			printf("\n");
		}
		else {
			printf("|역자 : %s\n", book["translator"].GetString());
		}
		printf("출판사 : %s\n", book["publisher"].GetString());
		printf("가격 : %d\n", book["cost"].GetInt());
		if (book["lend"].GetBool()) {
			printf("대여중");
		}
		
		printf("===================\n");
	}
}
