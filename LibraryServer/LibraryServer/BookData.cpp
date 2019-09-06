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

int BookData::CheckCanBorrow(int id)//0:대여가능 1:대여불가 2:존재하지 않음
{
	for (auto& book : bookData.GetArray()) {
		if (book["id"].GetInt() == id) {
			if (book["lend"].GetBool() == false) {
				printf("**대여요청 : %s  -> 대여가능\n", book["name"].GetString());
				book["lend"].SetBool = true;
				return 0;
			}
			else {
				printf("**대여요청 : %s  -> 대여불가\n", book["name"].GetString());
				return 1;
			}
		}
	}
	printf("**대여요청 : 존재하지 않는 책입니다.");
	return 2;
}
