#include "ClientSend.h"
#include <rapidjson/writer.h>
#include <cstdio>

ClientSend::ClientSend()
{
	requestBookList.SetObject();
	requestBookList.AddMember("code", Value().SetInt(1), requestBookList.GetAllocator());

	borrowBooks.SetObject();
	borrowBooks.AddMember("code", Value().SetInt(2), borrowBooks.GetAllocator());
	borrowBooks.AddMember("borrow", Value().SetArray(), borrowBooks.GetAllocator());//ºô¸± Ã¥ id

	returnBooks.SetObject();
	returnBooks.AddMember("code", Value().SetInt(3), borrowBooks.GetAllocator());
	returnBooks.AddMember("return", Value().SetArray(), borrowBooks.GetAllocator());//¹Ý³³ÇÒ Ã¥ id
}

ClientSend::~ClientSend()
{
	requestBookList.RemoveAllMembers();
	borrowBooks.RemoveAllMembers();
	returnBooks.RemoveAllMembers();
}

char * ClientSend::RequestBookList()
{
	StringBuffer buffer;
	buffer.Clear();
	
	Writer<StringBuffer> writer(buffer);
	requestBookList.Accept(writer);

	return _strdup(buffer.GetString());
}
char * ClientSend::BorrowBooks(int brrs[], int cnt)
{
	for (int i = 0; i < cnt; i++) {
		borrowBooks["borrow"].PushBack(Value().SetInt(brrs[i]), borrowBooks.GetAllocator());
	}
	StringBuffer buffer;
	buffer.Clear();

	Writer<StringBuffer> writer(buffer);
	borrowBooks.Accept(writer);
	borrowBooks["borrow"].Clear();

	return _strdup(buffer.GetString());
}
char * ClientSend::ReturnBooks(int brrs[], int cnt)
{
	for (int i = 0; i < cnt; i++) {
		returnBooks["return"].PushBack(Value().SetInt(brrs[i]), returnBooks.GetAllocator());
	}
	StringBuffer buffer;
	buffer.Clear();

	Writer<StringBuffer> writer(buffer);
	returnBooks.Accept(writer);
	returnBooks["return"].Clear();

	return _strdup(buffer.GetString());
}