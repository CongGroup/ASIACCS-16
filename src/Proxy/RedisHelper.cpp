#include "RedisHelper.h"

#include <redis3m/redis3m.hpp>
#include <string>
#include <string.h>
#include <iostream>
#include <stdint.h>

using namespace redis3m;
using namespace std;


RedisHelper::RedisHelper()
{
}


RedisHelper::~RedisHelper()
{
}


void RedisHelper::Open()
{
	cout << "Begin Create:" << endl;
	m_ptrConnection = connection::create();
	cout << "End Create !!!!!!!" << endl;
}

void RedisHelper::Close()
{

}

uint32_t RedisHelper::Get(const string &strKey, string &strVal)
{

	reply oReply = m_ptrConnection->run(command("GET") << strKey);
	strVal = oReply.str();

	return strVal.length();
}

uint32_t RedisHelper::Get(char *pKey, uint32_t uiKeyLen, string &strVal)
{
	string strKey;
	strKey.assign(pKey, uiKeyLen);

	reply oReply = m_ptrConnection->run(command("GET") << strKey);
	strVal = oReply.str();

	return strVal.length();

}

uint32_t RedisHelper::Get(char *pKey, uint32_t uiKeyLen, char *pOut, uint32_t uiOutLen)
{
	string strKey;
	strKey.assign(pKey, uiKeyLen);

	reply oReply = m_ptrConnection->run(command("GET") << strKey);
	string strVal = oReply.str();
	uint32_t uiLen = strVal.length();

	if (uiLen > uiOutLen)
	{
		return 0;
	}
	else
	{
		memcpy(pOut, strVal.c_str(), uiLen);

#ifdef DEBUG_REDIS_HELPER

		cout << pOut << endl;

#endif

		return uiLen;
	}

}

void RedisHelper::Put(const string &strKey, const string &strVal)
{

	m_ptrConnection->run(command("SET") << strKey << strVal);

#ifdef DEBUG_REDIS_HELPER

	std::cout << strKey << " " << strVal << std::endl;

#endif

	return;
}

void RedisHelper::Put(char *pKey, uint32_t uiKeyLen, char *pVal, uint32_t uiValLen)
{
	string strKey, strVal;
	strKey.assign(pKey, uiKeyLen);
	strVal.assign(pVal, uiValLen);

	m_ptrConnection->run(command("SET") << strKey << strVal);

#ifdef DEBUG_REDIS_HELPER

	std::cout << uiKeyLen << " " << uiValLen << std::endl;

#endif

	return;

}

