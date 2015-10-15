#include "RedisHelper.h"

#include <redis3m/redis3m.hpp>
#include <string>
#include <string.h>
#include <iostream>
#include <stdint.h>

using namespace redis3m;
connection::ptr_t c;
RedisHelper::RedisHelper()
{
}


RedisHelper::~RedisHelper()
{
}


void RedisHelper::Open()
{
	c = connection::create();
}

void RedisHelper::Close()
{

}

uint32_t RedisHelper::Get(char *pKey, uint32_t uiKeyLen, char *pOut, uint32_t uiOutLen)
{
	std::string sKey,sVal;
	sKey.append(pKey);
	reply r = c->run(command("GET") << sKey);
	sVal = r.str();
	uint32_t len = (unsigned) sVal.size();
	if (len > uiOutLen)
	{
		return 0;
	}
	else 
	{
		std::copy(sVal.begin(), sVal.end(), pOut);
		pOut[sVal.size()] = '\0';
		std::cout << pOut << std::endl;
		return len;
	}

}

void RedisHelper::Put(char *pKey, uint32_t uiKeyLen, char *pVal, uint32_t uiValLen)
{
	std::string sKey,sVal;
	sKey.append(pKey);
	sVal.append(pVal);
	c->run(command("SET") << sKey << sVal);
	std::cout << uiKeyLen << " " << uiValLen << std::endl;
	return;

}

