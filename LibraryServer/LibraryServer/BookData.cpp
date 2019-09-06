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
