#ifndef __CLIENT_CPP_H__
#define __CLIENT_CPP_H__

#include <iostream>
#include <string.h>
#include <string>
#include <stdint.h>
#include <vector>

#define SHA256_DIGEST_LENGTH 32

using namespace std;

class ClientCpp
{
public:
	ClientCpp();
	~ClientCpp();

	void InitKey(string stKey);

	void Get(string &_retVal, string stTable, string stKey, string stCol);

	void Put(string stTable, string stKey, string stCol, char *pVal, uint32_t uiLen);

	void GetCol(vector<string> &_retVal, string stTable, string stCol, uint32_t uiNum);


private:


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

};





#endif
