#pragma once
#include "rapidjson/document.h"
using namespace rapidjson;

class BookData
{
public:
	BookData();
	~BookData();
	char* SendBookList();
	int CheckCanBorrow(int id);
private:
	Document bookData;
};

