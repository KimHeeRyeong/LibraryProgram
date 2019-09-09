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
			printf("**�뿩��**\n");
		}
		
		printf("===================\n");
	}
}

void ServerReceive::PrintBrrList()
{
	printf("===================\n"); 
	for (auto& book : brrBooks.GetArray()) {

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
				printf("�ݳ� ����!\n");
			}
			index++;
		}
	}
	else {
		printf("�ݳ��� �����߽��ϴ�. �ٽ� �õ����ּ���.\n");
	}
	printf("===================\n");
}
void ServerReceive::BrrResult(const char str[])
{
	Document d(&brrBooks.GetAllocator());
	d.Parse(str);
	int i = d["result"].GetInt();
	if (i == 0) {
		printf("���� ����!\n");
		printf("===================\n");
		printf("��ȣ : %d\n", d["data"]["id"].GetInt());
		printf("���� : %s\n", d["data"]["name"].GetString());
		printf("���� : %s", d["data"]["writer"].GetString());
		if (d["data"]["translator"].IsNull()) {
			printf("\n");
		}
		else {
			printf("|���� : %s\n", d["data"]["translator"].GetString());
		}
		printf("���ǻ� : %s\n", d["data"]["publisher"].GetString());
		printf("���� : %d\n", d["data"]["cost"].GetInt());
		brrCnt++;
		brrBooks.PushBack(d["data"].GetObject(), brrBooks.GetAllocator());
	}
	else if(i == 1){
		printf("[�뿩 �Ұ�]�̹� �뿩���� å�Դϴ�.\n");
	}
	else {
		printf("[�뿩 �Ұ�]�������� �ʴ� id�Դϴ�.\n");
	}
	printf("===================\n");
}
bool ServerReceive::CheckCanReturn() {
	if (brrCnt == 0) {
		printf("===================\n");
		printf("�ݳ��� ������ �����ϴ�!\n");
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
	printf("�ش��ϴ� å�� �������� �ʽ��ϴ�.");
	return false;
}
