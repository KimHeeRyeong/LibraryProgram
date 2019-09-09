#include "ClientReceive.h"
#include <rapidjson/writer.h>
#include <cstdio>

ClientReceive::ClientReceive()
{
}


ClientReceive::~ClientReceive()
{
}

int ClientReceive::GetCode(const char str[])
{
	Document d;
	d.Parse(str);
	if (d.IsObject()) {
		int i = d["code"].GetInt();
		d.RemoveAllMembers();
		return i;
	}
	return -1;
}

char* ClientReceive::PrintRequestBrr(const char str[], BookData* bookData)
{
	Document d;
	d.Parse(str);
	brrResult = bookData->CheckCanBorrow(d["borrow"].GetInt());
	d.RemoveAllMembers();

	StringBuffer buffer;
	buffer.Clear();

	Writer<StringBuffer> writer(buffer);
	brrResult.Accept(writer);
	brrResult.RemoveAllMembers();

	return _strdup(buffer.GetString());
}
char* ClientReceive::ReturnBooks(const char str[], BookData* bookData) {
	Document d;
	d.Parse(str);
	returnResult = bookData->CheckCanReturn(d["return"].GetInt());
	d.RemoveAllMembers();

	StringBuffer buffer;
	buffer.Clear();

	Writer<StringBuffer> writer(buffer);
	returnResult.Accept(writer);
	returnResult.RemoveAllMembers();

	return _strdup(buffer.GetString());
}

