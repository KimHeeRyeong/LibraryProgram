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
};

