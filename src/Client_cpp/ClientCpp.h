#ifndef __CLIENT_CPP_H__
#define __CLIENT_CPP_H__

#include <iostream>
#include <string.h>
#include <string>
#include <stdint.h>
#include <vector>
#include <map>

#include "../Caravel/ThriftAdapt.h"

#include "SimConHash.h"
#include "TProxyService.h"

#include "DemoConfig.h"

#define SHA256_DIGEST_LENGTH 32
#define INDEX_STOP_FLAG 1234567890

using namespace proxyserver;
using namespace caravel;
using namespace std;

class ClientCpp
{
public:
	ClientCpp();
	~ClientCpp();

	void InitKey(string stKey);

	void Open();
	void Close();

	void InitExample(uint32_t uiServerNum = DEMO_SERVER_NUM);

	void Get(string &_retVal, string stTable, string stKey, string stCol);

	void Put(string stTable, string stKey, string stCol, char *pVal, uint32_t uiLen, bool bIndex);

	void GetCol(vector<string> &_retVal, string stTable, string stCol, uint32_t uiNum);


private:

	void m_Decrypt(string &strCiphertext, string &strPlaintext);
	void m_Encrypt(string &strCiphertext, char *pPlaintext, uint32_t uiPlaintextLen);

	//For counter
	map<string, uint32_t> m_mapCounter;

	//For trapdoor to Key
	//<Table + Column + Key> || PK1 => Trapdoor
	char m_szPk1[SHA256_DIGEST_LENGTH];

	//For trapdoor to column counter
	char m_szPk2[SHA256_DIGEST_LENGTH];

	//For Index Column
	//<Table + Column + PK3> || Counter => ColumnKey
	char m_szPk3[SHA256_DIGEST_LENGTH];

	//For Index Column Value Mask
	//<Table + Column + PK4> || Counter => Mask
	char m_szPk4[SHA256_DIGEST_LENGTH];

	//For protect data by AES CBC 256
	char m_szPk5[SHA256_DIGEST_LENGTH];

	SimConHash<ThriftAdapt<TProxyServiceClient>* > m_SimConHash;

};





#endif
