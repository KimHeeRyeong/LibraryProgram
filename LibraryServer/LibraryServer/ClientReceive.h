#pragma once
#include "BookData.h"
#include "rapidjson/document.h"
using namespace rapidjson;
class ClientReceive
{
public:
	ClientReceive();
	~ClientReceive();
	int GetCode(const char str[]);
	char* PrintRequestBrr(const char str[], BookData* bookData);
	char * ReturnBooks(const char str[], BookData * bookData);
private:
	Document brrResult;
	Document returnResult;
};

