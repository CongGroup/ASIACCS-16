#include "RedisHelper.h"

#include <redis3m/redis3m.hpp>
#include <string>
#include <string.h>
#include <iostream>
#include <stdint.h>
#include <map>

using namespace redis3m;
using namespace std;


RedisHelper::RedisHelper()
{
}


RedisHelper::~RedisHelper()
{
}


void RedisHelper::OpenClusterPool(const std::string& host, const unsigned int port)
{
    m_ptrClusterPool = simple_pool::create(host, port);
}


void RedisHelper::CloseClusterPool()
{

}


uint32_t RedisHelper::ClusterPoolGet(const string &strKey, string &strVal)
{
    //The first step

    m_ptrClusterPool->run_with_connection<void>([&](connection::ptr_t conn)
    {
        strVal = conn->run(command("GET")(strKey)).str();
    });

    if (strVal.compare(0, 6, "MOVED ") == 0)
    {
        //Second step
        uint32_t uiIPBeg = strVal.find_last_of(' ');
        uint32_t uiIPEnd = strVal.find_last_of(':');
        string strIP = strVal.substr(uiIPBeg, uiIPEnd - uiIPBeg);
        string strPort = strVal.substr(uiIPEnd + 1, strVal.length() - uiIPEnd);
        uint32_t uiPort;
        sscanf(strPort.c_str(), "%u", &uiPort);

        simple_pool::ptr_t ptrPool;

        //find the simple_pool
        if (m_mapPtrPool.find(strIP) != m_mapPtrPool.end())
        {
            //find connect
            ptrPool = m_mapPtrPool[strIP];
        }
        else
        {
            ptrPool = simple_pool::create(strIP.c_str(), uiPort);
            m_mapPtrPool[strIP] = ptrPool;
        }

        ptrPool->run_with_connection<void>([&](connection::ptr_t conn)
        {
            strVal = conn->run(command("GET")(strKey)).str();
        });

        return strVal.length();

    }
    else
    {
        return strVal.length();
    }

}


void RedisHelper::ClusterPoolPut(const string &strKey, const string &strVal)
{
    m_ptrClusterPool->run_with_connection<void>([&](connection::ptr_t conn)
    {
        conn->run(command("SET")(strKey)(strVal));
    });
}


void RedisHelper::OpenPool(const std::string& host, const unsigned int port)
{
    m_ptrPool = simple_pool::create(host, port);
}

void RedisHelper::ClosePool()
{

}


uint32_t RedisHelper::PoolGet(const string &strKey, string &strVal)
{
	m_ptrPool->run_with_connection<void>([&](connection::ptr_t conn)
	{
		strVal = conn->run(command("GET")(strKey)).str();
	});

    return strVal.length();

}

void RedisHelper::PoolPut(const string &strKey, const string &strVal)
{
	m_ptrPool->run_with_connection<void>([&](connection::ptr_t conn)
	{
		conn->run(command("SET")(strKey)(strVal));
	});
}


void RedisHelper::Open(const std::string& host, const unsigned int port)
{
    m_ptrConnection = connection::create(host, port);
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

