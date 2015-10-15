#ifndef __REDIS_HELPER_H__
#define __REDIS_HELPER_H__


#include <string>
#include <string.h>
#include <iostream>
#include <stdint.h>

using namespace std;


class RedisHelper
{
public:
	RedisHelper();
	~RedisHelper();


private:

	//For open a connection to Redis server.
	void Open();

	//For close the connection to Redis server.
	void Close();

	//Get function
	uint32_t Get(char *pKey, uint32_t uiKeyLen, char *pOut, uint32_t uiOutLen);

	//Put function
	void Put(char *pKey, uint32_t uiKeyLen, char *pVal, uint32_t uiValLen);

};



#endif

