#pragma once
#include "rapidjson/document.h"
using namespace rapidjson;
class ClientSend
{
public:
	ClientSend();
	~ClientSend();
	char* RequestBookList();
	char* BorrowBook(int brr);
	char * ReturnBook(int brr);
	char* ExitProgram();

private:
	Document requestBookList;
	Document borrowBooks;
	Document returnBooks;
	Document exit;
};

