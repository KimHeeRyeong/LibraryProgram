#include "ClientReceive.h"


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
	int i = d["code"].GetInt();
	d.RemoveAllMembers();
	return i;
}

char* ClientReceive::PrintRequestBrr(const char str[], BookData* bookData)
{
	Document d;
	d.Parse(str);
	for (auto& id : d["borrow"].GetArray()) {
		bookData->CheckCanBorrow(id.GetInt());
	}
	d.RemoveAllMembers();
	return nullptr;
}

