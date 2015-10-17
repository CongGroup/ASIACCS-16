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
	if(argc != 5)
	{
		cout<<"usage : ./TestSystem [DataNodeNum] [A] [B] [C]"<<endl;
		cout<<"The test will begin at [A] ."<<endl;
		cout<<"The test will consist [B] seconds"<<endl;
		cout<<"The Seed is [C] ."<<endl;
		return 0;
	}

	uint32_t uiBeg, uiTime, uiSeed, uiDataNodeNum;

	sscanf(argv[1], "%u", &uiDataNodeNum);
	sscanf(argv[2], "%u", &uiBeg);
	sscanf(argv[3], "%u", &uiTime);
	sscanf(argv[4], "%u", &uiSeed);

	srand(uiSeed);

	uint32_t uiCurTime;
	uint32_t uiBegTime = uiBeg;
	uint32_t uiEndTime = uiBegTime + uiTime;

	char szBuf[1000];
	memset(szBuf, 0, sizeof(szBuf));
	string stKey;
	string stScore;

	ClientCpp client;
	client.InitKey(DEMO_SECURITY_KEY);
	client.InitExample();
	client.Open();

	cout << "Begin to basic test ..." << endl;
	cout << "-----------------------------------------------------------------------------" << endl;

	uint32_t uiCnt = 0;
	while(true)
	{

		uiCurTime = time(NULL);

		if(uiCurTime < uiBegTime)
		{
			continue;
		}

		if(uiCurTime >= uiEndTime)
		{
			break;
		}

		(*(uint32_t*)szBuf)++;
		stKey.assign(szBuf);
		(*(uint32_t*)szBuf)++;
		stScore.assign(szBuf);

#ifdef DEF_INSERT_INDEX

		client.Put("StudentScoreTable", stKey, "Score", (char*)stScore.c_str(), stScore.length(), true);

#else

		client.Put("StudentScoreTable", stKey, "Score", (char*)stScore.c_str(), stScore.length(), false);

#endif

		for(int i = 0; i < 19; i++)
		{
			string stReturnScore;
			client.Get(stReturnScore, "StudentScoreTable", stKey, "Score");
		}

		uiCnt++;
	}

	cout << uiCnt << endl;
	return 0;
}
