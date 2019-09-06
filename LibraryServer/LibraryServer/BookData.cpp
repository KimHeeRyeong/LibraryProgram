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

int BookData::CheckCanBorrow(int id)//0:�뿩���� 1:�뿩�Ұ� 2:�������� ����
{
	for (auto& book : bookData.GetArray()) {
		if (book["id"].GetInt() == id) {
			if (book["lend"].GetBool() == false) {
				printf("**�뿩��û : %s  -> �뿩����\n", book["name"].GetString());
				book["lend"].SetBool = true;
				return 0;
			}
			else {
				printf("**�뿩��û : %s  -> �뿩�Ұ�\n", book["name"].GetString());
				return 1;
			}
		}
	}
	printf("**�뿩��û : �������� �ʴ� å�Դϴ�.");
	return 2;
}
