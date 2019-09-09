#include "ServerReceive.h"



ServerReceive::ServerReceive()
{
	brrCnt = 0;
	brrBooks.SetArray();
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
			printf("**대여중**\n");
		}
		
		printf("===================\n");
	}
}

void ServerReceive::PrintBrrList()
{
	printf("===================\n"); 
	for (auto& book : brrBooks.GetArray()) {

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
		printf("===================\n");
	}
	
}
void ServerReceive::ReturnResult(const char str[])
{
	Document d(&brrBooks.GetAllocator());
	d.Parse(str);
	int i = d["result"].GetInt();
	int returnId = d["id"].GetInt();
	printf("===================\n");
	if (i == 0) {
		brrCnt--;
		int index=0;
		for (auto& book : brrBooks.GetArray()) {
			if (book["id"].GetInt() == returnId) {
				brrBooks.Erase(brrBooks.Begin() + index);
				printf("반납 성공!\n");
			}
			index++;
		}
	}
	else {
		printf("반납에 실패했습니다. 다시 시도해주세요.\n");
	}
	printf("===================\n");
}
void ServerReceive::BrrResult(const char str[])
{
	Document d(&brrBooks.GetAllocator());
	d.Parse(str);
	int i = d["result"].GetInt();
	if (i == 0) {
		printf("대출 성공!\n");
		printf("===================\n");
		printf("번호 : %d\n", d["data"]["id"].GetInt());
		printf("제목 : %s\n", d["data"]["name"].GetString());
		printf("저자 : %s", d["data"]["writer"].GetString());
		if (d["data"]["translator"].IsNull()) {
			printf("\n");
		}
		else {
			printf("|역자 : %s\n", d["data"]["translator"].GetString());
		}
		printf("출판사 : %s\n", d["data"]["publisher"].GetString());
		printf("가격 : %d\n", d["data"]["cost"].GetInt());
		brrCnt++;
		brrBooks.PushBack(d["data"].GetObject(), brrBooks.GetAllocator());
	}
	else if(i == 1){
		printf("[대여 불가]이미 대여중인 책입니다.\n");
	}
	else {
		printf("[대여 불가]존재하지 않는 id입니다.\n");
	}
	printf("===================\n");
}
bool ServerReceive::CheckCanReturn() {
	if (brrCnt == 0) {
		printf("===================\n");
		printf("반납할 도서가 없습니다!\n");
		printf("===================\n");
		return false;
	}
	return true;
}
bool ServerReceive::CheckBrrBookID(int i) {
	for (auto& book : brrBooks.GetArray()) {
		if (book["id"].GetInt() == i) {
			return true;
		}
	}
	printf("해당하는 책이 존재하지 않습니다.");
	return false;
}
