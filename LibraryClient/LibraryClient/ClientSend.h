#pragma once
#include "rapidjson/document.h"
using namespace rapidjson;
class ClientSend
{
public:
	ClientSend();
	~ClientSend();
	char* RequestBookList();
	char* BorrowBooks(int brrs[], int cnt);
	char * ReturnBooks(int brrs[], int cnt);

private:
	Document requestBookList;
	Document borrowBooks;
	Document returnBooks;
};

