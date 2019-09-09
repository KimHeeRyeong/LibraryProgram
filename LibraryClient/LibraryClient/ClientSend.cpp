#include "ClientSend.h"
#include <rapidjson/writer.h>
#include <cstdio>

ClientSend::ClientSend()
{
	requestBookList.SetObject();
	requestBookList.AddMember("code", Value().SetInt(1), requestBookList.GetAllocator());

	borrowBooks.SetObject();
	borrowBooks.AddMember("code", Value().SetInt(1), borrowBooks.GetAllocator());
	borrowBooks.AddMember("borrow", Value().SetInt(-1), borrowBooks.GetAllocator());//ºô¸± Ã¥ id

	returnBooks.SetObject();
	returnBooks.AddMember("code", Value().SetInt(2), returnBooks.GetAllocator());
	returnBooks.AddMember("return", Value().SetInt(-1), returnBooks.GetAllocator());//¹Ý³³ÇÒ Ã¥ id

	exit.SetObject();
	exit.AddMember("code", Value().SetInt(3), exit.GetAllocator());

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
char * ClientSend::BorrowBook(int brr)
{
	borrowBooks["borrow"].SetInt(brr);
	StringBuffer buffer;
	buffer.Clear();

	Writer<StringBuffer> writer(buffer);
	borrowBooks.Accept(writer);
	borrowBooks["borrow"].SetInt(-1);

	return _strdup(buffer.GetString());
}
char * ClientSend::ReturnBook(int brr)
{
	returnBooks["return"].SetInt(brr);
	StringBuffer buffer;
	buffer.Clear();

	Writer<StringBuffer> writer(buffer);
	returnBooks.Accept(writer);
	returnBooks["return"].SetInt(-1);

	return _strdup(buffer.GetString());
}

char * ClientSend::ExitProgram()
{
	StringBuffer buffer;
	buffer.Clear();

	Writer<StringBuffer> writer(buffer);
	exit.Accept(writer);

	return _strdup(buffer.GetString());
}
