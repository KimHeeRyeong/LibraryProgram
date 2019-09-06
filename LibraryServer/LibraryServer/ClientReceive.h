#pragma once
#include "BookData.h"
class ClientReceive
{
public:
	ClientReceive();
	~ClientReceive();
	int GetCode(const char str[]);
	char* PrintRequestBrr(const char str[], BookData* bookData);
};

