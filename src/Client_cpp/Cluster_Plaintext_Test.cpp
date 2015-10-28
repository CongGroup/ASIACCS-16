#include <iostream>
#include <string.h>
#include <string>
#include <stdint.h>
#include <vector>

#include "DemoConfig.h"
#include "../Proxy/RedisHelper.h"
#include "../Caravel/TimeDiff.h"

using namespace std;
using namespace caravel;

const int MAXRECORD = 1000000 + 100;
const int iNum = 1000000;
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


    RedisHelper redisHelper;
    RedisHelper *pRedisHelper = &redisHelper;

    //Init
    pRedisHelper->Open("10.4.0.7", 6379);

    uint32_t uiTimeDiff;

    cout << "Begin to basic test ..." << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

    //Initialize random seed
    srand(uiSeed);
    char charRandom = (char) (rand() % 26 + 'A');
    // cout << charRandom << endl;


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

    TimeDiff::DiffTimeInMicroSecond();

    for (int i = 0; i < iNum; ++i)
    {
        (*pKeyCursorNum)++;
        strInput[i] = strKey;
        pRedisHelper -> Put(strKey, strScore);
    }

    uiTimeDiff = TimeDiff::DiffTimeInMicroSecond();

    cout << "Put 1,000,000 items cost time : " << uiTimeDiff << endl;

    //Test Get operation
    string strVal;

    TimeDiff::DiffTimeInMicroSecond();
    for (int i = 0; i < iNum; ++i)
    {
        string stReturnScore;
        pRedisHelper -> Get(strKey, stReturnScore);
    }
    uiTimeDiff = TimeDiff::DiffTimeInMicroSecond();

    cout << "Get 1,000,000 items cost time : " << uiTimeDiff << endl;

    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "Finish Test" << endl;

}
