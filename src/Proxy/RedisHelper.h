#ifndef __REDIS_HELPER_H__
#define __REDIS_HELPER_H__


#include <string>
#include <string.h>
#include <iostream>
#include <stdint.h>
#include <map>

#include <redis3m/redis3m.hpp>

using namespace std;
using namespace redis3m;

class RedisHelper
{
public:
	RedisHelper();
	~RedisHelper();

	/*Multi Connection Pool*/
	void OpenClusterPool(const std::string& host = "localhost", const unsigned int port = 6379);
	void CloseClusterPool();

	uint32_t ClusterPoolGet(const string &strKey, string &strVal);
	void ClusterPoolPut(const string &strKey, const string &strVal);

	/*Connection Pool*/

	void OpenPool(const std::string& host = "localhost", const unsigned int port = 6379);
	void ClosePool();

	uint32_t PoolGet(const string &strKey, string &strVal);
	void PoolPut(const string &strKey, const string &strVal);

	/*Single Use*/

	//For open a connection to Redis server.
	void Open(const std::string& host = "localhost", const unsigned int port = 6379);

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
    simple_pool::ptr_t m_ptrPool;
    
    map<string, simple_pool::ptr_t> m_mapPtrPool;
    simple_pool::ptr_t m_ptrClusterPool;

};



#endif

