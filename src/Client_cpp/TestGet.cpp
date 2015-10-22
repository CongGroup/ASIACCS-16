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
	if (argc != 6)
	{
		cout << "usage : ./" << argv[0] << " [DataNodeNum] [A] [B] [C] [D]" << endl;
		cout << "The test will begin at [A] ." << endl;
		cout << "The test will consist [B] seconds" << endl;
		cout << "The Key size is [C] ." << endl;
		cout << "The Seed is [D] ." << endl;
		return 0;
	}


	//Get the params from command line
	uint32_t uiBeg, uiTime, uiSeed, uiServerNum, uiKeyLen;
	sscanf(argv[1], "%u", &uiServerNum);
	sscanf(argv[2], "%u", &uiBeg);
	sscanf(argv[3], "%u", &uiTime);
	sscanf(argv[4], "%u", &uiKeyLen);
	sscanf(argv[5], "%u", &uiSeed);

	//Compute the params
	uint32_t uiCurTime;
	uint32_t uiBegTime = uiBeg;
	uint32_t uiEndTime = uiBegTime + uiTime;

	//Initialize random seed
	srand(uiSeed);
	char charRandom = (char) (rand() % 26 + 'A');
	cout << charRandom << endl;

	//Init the cache for key
	string strKey;
	strKey.assign(uiKeyLen, charRandom);
	//This number will be changed to simulate the random key.
	//[ {OOOO} {XXXXXXXXXXXXXXXXXXXXXXXXXXXXX} ]  {OOOO} means the number;  {XXXX} means the padding for key
	//strKey should not be assign
	uint32_t *pKeyCursorNum;
	pKeyCursorNum = (uint32_t*)(strKey.c_str());
	*pKeyCursorNum = 0;

	//Init strScore	
	string strScore;
	strScore.assign(128, 'A');

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

#ifdef DEF_INSERT_INDEX

		client.Put("StudentScoreTable", strKey, "Score", (char*)strScore.c_str(), strScore.length(), true);

#else

		client.Put("StudentScoreTable", strKey, "Score", (char*)strScore.c_str(), strScore.length(), false);

#endif

		for (int i = 0; i < 19; i++)
		{
			string stReturnScore;
			client.Get(stReturnScore, "StudentScoreTable", strKey, "Score");
		}

		uiCnt++;
	}

	cout << uiCnt << endl;

	return 0;
}




