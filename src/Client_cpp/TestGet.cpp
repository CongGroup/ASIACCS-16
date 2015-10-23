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

const int MAXRECORD = 100000 + 100;
const int iNum = 10000;
string strInput[MAXRECORD];

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

	for (int i = 0; i < iNum; ++i)
	{
		(*pKeyCursorNum)++;
		strInput[i] = strKey;
		cout << "Start to put: " << i << " " << strKey << endl;
		cout << "StudentScoreTable" << " " <<  strKey << " " <<  "Score" << " " << (char*)strScore.c_str() << " " <<  strScore.length() << endl;
#ifdef DEF_INSERT_INDEX

		client.Put("StudentScoreTable", strKey, "Score", (char*)strScore.c_str(), strScore.length(), true);

#else

		client.Put("StudentScoreTable", strKey, "Score", (char*)strScore.c_str(), strScore.length(), false);
		cout << "Done. " << i << " " << strKey << endl;

#endif
	}

	uint32_t uiBegTime = time(NULL);
	for (int i = 0; i < iNum; ++i)
	{
		string stReturnScore;
		client.Get(stReturnScore, "StudentScoreTable", strInput[i], "Score");
	}
	uint32_t uiDuration = time(NULL) - uiBegTime;

	cout << uiDuration << endl;

	return 0;
}




