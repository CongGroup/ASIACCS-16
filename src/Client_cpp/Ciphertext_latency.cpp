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
	if (argc != 5)
	{
		cout << "usage : ./" << argv[0] << " [DataNodeNum] [KeyLen] [ValLen] [Times]" << endl;
		cout << "The Key size is [X] ." << endl;
        cout << "The Value size is [X] ." << endl;
        cout << "The num of times = [X]" << endl;
		return 0;
	}

	//Get the params from command line
	uint32_t uiServerNum, uiKeyLen, uiValLen, uiOption, uiNum;
	sscanf(argv[1], "%u", &uiServerNum);
	sscanf(argv[2], "%u", &uiKeyLen);
    sscanf(argv[2], "%u", &uiValLen);
    sscanf(argv[4], "%u", &uiNum);

	//Init the cache for key
	string strKey;
	strKey.assign(uiKeyLen, '0');
	//This number will be changed to simulate the random key.
	//[ {OOOO} {XXXXXXXXXXXXXXXXXXXXXXXXXXXXX} ]  {OOOO} means the number;  {XXXX} means the padding for key
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

    //For remember the time
	uint32_t uiTimeDiff;

    //init array for store keys
    string *arStrInput = new string[uiNum];

    //Init key pairs
    for (uint32_t uiCur = 0; uiCur < uiNum; uiCur++)
    {
        (*pKeyCursorNum)++;
        arStrInput[uiCur].assign(strKey.c_str(), uiKeyLen);
    }

    TimeDiff::DiffTimeInMicroSecond();

	//Test Put operation
	for (uint32_t uiCur = 0; uiCur < uiNum; uiCur++)
	{
		
#ifdef DEF_INSERT_INDEX

		client.Put("StudentScoreTable", arStrInput[uiCur], "Score", (char*)strVal.c_str(), strVal.length(), true);

#else

		client.Put("StudentScoreTable", arStrInput[uiCur], "Score", (char*)strVal.c_str(), strVal.length(), false);

#endif
	}

	uiTimeDiff = TimeDiff::DiffTimeInMicroSecond();

	cout << "Putting " <<  uiNum << " items cost time: " << uiTimeDiff << endl;

	//Test Get operation

	TimeDiff::DiffTimeInMicroSecond();

    for (uint32_t uiCur = 0; uiCur < uiNum; uiCur++)
	{
		string stReturnScore;
		client.Get(stReturnScore, "StudentScoreTable", arStrInput[uiCur], "Score");
	}

	uiTimeDiff = TimeDiff::DiffTimeInMicroSecond();
	cout << "Getting " <<  uiNum << " items cost time: " << uiTimeDiff << endl; 


    //Test GetCol Operation

    vector<string> vecResult;

    TimeDiff::DiffTimeInMicroSecond();

    client.GetCol(vecResult, "StudentScoreTable", "Score", 1000);

    uiTimeDiff = TimeDiff::DiffTimeInMicroSecond();

    cout << "Pull 1000 items from GetCol cost time: " << uiTimeDiff << endl;

	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "Finish Test" << endl;

    delete[] arStrInput;

}
