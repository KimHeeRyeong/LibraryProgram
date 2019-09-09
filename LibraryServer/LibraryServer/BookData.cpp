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

Document BookData::CheckCanBorrow(int id)//0:대여가능 1:대여불가 2:존재하지 않음
{
	Document d;
	d.SetObject();
	d.AddMember("result", Value().SetInt(2), d.GetAllocator());
	d.AddMember("data", Value().SetObject(), d.GetAllocator());
	for (auto& book : bookData.GetArray()) {
		if (book["id"].GetInt() == id) {
			if (book["lend"].GetBool() == false) {
				printf("**대여요청 : %s  -> 대여가능\n", book["name"].GetString());
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
				printf("**대여요청 : %s  -> 대여불가\n", book["name"].GetString());
				d["result"].SetInt(1);
				return d;
			}
		}
	}
	printf("**대여요청 : 존재하지 않는 책입니다.");
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
				printf("**반납요청 : %s  -> 반납완료\n", book["name"].GetString());
				d["result"].SetInt(0);
				d["id"].SetInt(id);
				book["lend"].SetBool(false);
				return d;
			}
			else {
				printf("**반납요청 : %s  -> 반납불가\n", book["name"].GetString());
				d["result"].SetInt(1);
				return d;
			}
		}
	}
	printf("**존재하지 않는 id  -> 반납불가\n");
	return d;
}
