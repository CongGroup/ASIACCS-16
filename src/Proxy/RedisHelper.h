#ifndef __REDIS_HELPER_H__
#define __REDIS_HELPER_H__


#include <string>
#include <string.h>
#include <iostream>
#include <stdint.h>

#include <redis3m/redis3m.hpp>

using namespace std;
using namespace redis3m;

class RedisHelper
{
public:
	RedisHelper();
	~RedisHelper();

	//For open a connection to Redis server.
	void Open();

	//For close the connection to Redis server.
	void Close();

	//Get function
	uint32_t Get(char *pKey, uint32_t uiKeyLen, char *pOut, uint32_t uiOutLen);
	uint32_t Get(char *pKey, uint32_t uiKeyLen, string &strVal);
	uint32_t Get(const string &strKey, string &strVal);

	//Put function
	void Put(char *pKey, uint32_t uiKeyLen, char *pVal, uint32_t uiValLen);
	void Put(const string &strKey, const string &strVal);

private:

	connection::ptr_t m_ptrConnection;


};



#endif

