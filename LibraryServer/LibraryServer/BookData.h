#pragma once
#include "rapidjson/document.h"
using namespace rapidjson;

class BookData
{
public:
	BookData();
	~BookData();
	char* SendBookList();
	Document CheckCanBorrow(int id);
	Document CheckCanReturn(int id);
private:
	Document bookData;
};

