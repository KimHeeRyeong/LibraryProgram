#pragma once
#include "rapidjson/document.h"
using namespace rapidjson;

class BookData
{
public:
	BookData();
	~BookData();
	char* SendBookList();
private:
	Document bookData;
};

