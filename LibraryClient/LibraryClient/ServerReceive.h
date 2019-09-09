#pragma once
#include "rapidjson/document.h"
#include <cstdio>

using namespace rapidjson;
class ServerReceive
{
public:
	ServerReceive();
	~ServerReceive();
	void PrintList(const char str[]);
	void PrintBrrList();
	void ReturnResult(const char str[]);
	void BrrResult(const char str[]);
	bool CheckCanReturn();
	bool CheckBrrBookID(int i);
private:
	int brrCnt;
	Document brrBooks;
};

