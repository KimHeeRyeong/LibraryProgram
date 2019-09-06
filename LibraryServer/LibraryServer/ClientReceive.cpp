#include "ClientReceive.h"
#include "BookData.h"


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
