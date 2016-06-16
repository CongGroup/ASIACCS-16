#include <iostream>
#include <string.h>
#include <string>
#include <stdint.h>
#include <vector>

#include "DemoConfig.h"
#include "ClientCpp.h"
#include "../Caravel/TimeDiff.h"

using namespace std;
using namespace caravel;

int main(int argc, char **argv)
{
	if (argc != 8)
	{
		cout << "usage : ./" << argv[0] << " [DataNodeNum] [A] [B] [C] [Size] [D] [E]" << endl;
		cout << "The test will begin at [A] ." << endl;
		cout << "The test will consist [B] seconds" << endl;
		cout << "The Key size is [C] ." << endl;
		cout << "The Value Size is [Size]" << endl;
		cout << "0 for put. 1 for get. 2 for getCol. 3 for write heavy. 4 for half write-read" << endl;
		cout << "The Seed is [E] ." << endl;
		return 0;
	}


	//Get the params from command line
	uint32_t uiBeg, uiTime, uiSeed, uiServerNum, uiKeyLen, uiValLen, uiOption;
	sscanf(argv[1], "%u", &uiServerNum);
	sscanf(argv[2], "%u", &uiBeg);
	sscanf(argv[3], "%u", &uiTime);
	sscanf(argv[4], "%u", &uiKeyLen);
	sscanf(argv[5], "%u", &uiValLen);
	sscanf(argv[6], "%u", &uiOption);
	sscanf(argv[7], "%u", &uiSeed);

	//Compute the params
	uint32_t uiCurTime;
	uint32_t uiBegTime = uiBeg;
	uint32_t uiEndTime = uiBegTime + uiTime;

	//Init the cache for key
	string strKey;
	strKey.assign(uiKeyLen, '0');
	//This number will be changed to simulate the random key.
	//[ {OOOO} {XXXXXXXXXXXXXXXXXXXXXXXXXXXXX} ]  {OOOO} for the number;  {XXXX} for the padding
	//strKey should not be assign
	uint32_t *pKeyCursorNum;
	pKeyCursorNum = (uint32_t*)(strKey.c_str());
	*pKeyCursorNum = 0;

	//Init strVal	
	string strVal;
	strVal.assign(uiValLen, 'A');

	//Init the client to server
	ClientCpp client;
	client.InitKey(DEMO_SECURITY_KEY);
	client.InitExample(uiServerNum);
	client.Open();

	uint32_t uiCnt = 0;
	while (true)
	{
		uiCurTime = time(NULL);

		if (uiCurTime < uiBegTime)
		{
			continue;
		}

		if (uiCurTime >= uiEndTime)
		{
			break;
		}

		(*pKeyCursorNum)++;

		//Put
		if (0 == uiOption)
		{
#ifdef DEF_INSERT_INDEX
			client.Put("StudentScoreTable", strKey, "Score", (char*)strVal.c_str(), strVal.length(), true);
#else
			client.Put("StudentScoreTable", strKey, "Score", (char*)strVal.c_str(), strVal.length(), false);
#endif
		}
		//Get
		else if (1 == uiOption)
		{
			string stReturnScore;
			client.Get(stReturnScore, "StudentScoreTable", strKey, "Score");
		}
		else if (2 == uiOption)
		{
			//GetCol
		}
		else if(3 == uiOption)
		{

			//Read Heavy

#ifdef DEF_INSERT_INDEX
			client.Put("StudentScoreTable", strKey, "Score", (char*)strVal.c_str(), strVal.length(), true);
#else
			client.Put("StudentScoreTable", strKey, "Score", (char*)strVal.c_str(), strVal.length(), false);
#endif

			for (int i = 0; i < 19; i++)
			{
				uiCnt++;
				string stReturnScore;
				(*pKeyCursorNum)++;
				client.Get(stReturnScore, "StudentScoreTable", strKey, "Score");
			}

		}
		else if (4 == uiOption)
		{
			//Half Write Heavy

#ifdef DEF_INSERT_INDEX
			client.Put("StudentScoreTable", strKey, "Score", (char*)strVal.c_str(), strVal.length(), true);
#else
			client.Put("StudentScoreTable", strKey, "Score", (char*)strVal.c_str(), strVal.length(), false);
#endif

			uiCnt++;

			string stReturnScore;
			client.Get(stReturnScore, "StudentScoreTable", strKey, "Score");

			

		}
		else
		{
			cout << "Error Operation !" << endl;
			return 0;
		}

		uiCnt++;
	}
	
	cout << uiCnt << endl;

	client.Close();

	return 0;
}




