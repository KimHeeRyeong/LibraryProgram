#include "BookData.h"
#include "rapidjson/filereadstream.h"
#include <rapidjson/writer.h>
#include <cstdio>

BookData::BookData()
{
	FILE* fp = fopen("books.json", "rb");

	char readBuffer[500];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	bookData.ParseStream(is);

	fclose(fp);
}

BookData::~BookData()
{
}

char * BookData::SendBookList()
{
	StringBuffer buffer;
	buffer.Clear();

	Writer<StringBuffer> writer(buffer);
	bookData.Accept(writer);

	return _strdup(buffer.GetString());
}

Document BookData::CheckCanBorrow(int id)//0:�뿩���� 1:�뿩�Ұ� 2:�������� ����
{
	Document d;
	d.SetObject();
	d.AddMember("result", Value().SetInt(2), d.GetAllocator());
	d.AddMember("data", Value().SetObject(), d.GetAllocator());
	for (auto& book : bookData.GetArray()) {
		if (book["id"].GetInt() == id) {
			if (book["lend"].GetBool() == false) {
				printf("**�뿩��û : %s  -> �뿩����\n", book["name"].GetString());
				book["lend"].SetBool(true);
				d["result"].SetInt(0);
				d["data"].AddMember("id",Value().SetInt(book["id"].GetInt()),d.GetAllocator());
				d["data"].AddMember("name", Value().SetString(book["name"].GetString(), d.GetAllocator()), d.GetAllocator());
				d["data"].AddMember("writer", Value().SetString(book["writer"].GetString(), d.GetAllocator()), d.GetAllocator());
				if (book["translator"].IsNull()) {
					d["data"].AddMember("translator", Value().SetNull(), d.GetAllocator());
				}
				else {
					d["data"].AddMember("translator", Value().SetString(book["translator"].GetString(), d.GetAllocator()), d.GetAllocator());
				}
				d["data"].AddMember("publisher", Value().SetString(book["publisher"].GetString(), d.GetAllocator()), d.GetAllocator());
				d["data"].AddMember("cost", Value().SetInt(book["cost"].GetInt()), d.GetAllocator());
				return d;
			}
			else {
				printf("**�뿩��û : %s  -> �뿩�Ұ�\n", book["name"].GetString());
				d["result"].SetInt(1);
				return d;
			}
		}
	}
	printf("**�뿩��û : �������� �ʴ� å�Դϴ�.");
	d["result"].SetInt(2);
	return d;
}
Document BookData::CheckCanReturn(int id) {
	Document d;
	d.SetObject();
	d.AddMember("result", Value().SetInt(2), d.GetAllocator());
	d.AddMember("id", Value().SetInt(-1), d.GetAllocator());
	for (auto& book : bookData.GetArray()) {
		if (book["id"].GetInt() == id) {
			if (book["lend"].GetBool() == true) {
				printf("**�ݳ���û : %s  -> �ݳ��Ϸ�\n", book["name"].GetString());
				d["result"].SetInt(0);
				d["id"].SetInt(id);
				book["lend"].SetBool(false);
				return d;
			}
			else {
				printf("**�ݳ���û : %s  -> �ݳ��Ұ�\n", book["name"].GetString());
				d["result"].SetInt(1);
				return d;
			}
		}
	}
	printf("**�������� �ʴ� id  -> �ݳ��Ұ�\n");
	return d;
}
