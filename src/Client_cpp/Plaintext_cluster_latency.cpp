#include <iostream>
#include <string.h>
#include <string>
#include <stdint.h>
#include <vector>

#include "DemoConfig.h"
#include "../Caravel/RedisHelper.h"
#include "../Caravel/TimeDiff.h"

using namespace std;
using namespace caravel;

const int MAXRECORD = 1000000 + 100;
const int iNum = 10000;
string strInput[MAXRECORD];

int main(int argc, char **argv)
{

    if (argc != 6)
    {
        cout << "usage : ./" << argv[0] << " [DataNodeNum] [KeyLen] [ValLen] [Times]" << endl;
        cout << "The Key size is [X] ." << endl;
        cout << "The Value size is [X] ." << endl;
        cout << "The num of times = [X]" << endl;
        cout << "The Seed is [E] ." << endl;
        return 0;
    }

    //Get the params from command line
    uint32_t uiServerNum, uiKeyLen, uiValLen, uiOption, uiNum, uiSeed;
    sscanf(argv[1], "%u", &uiServerNum);
    sscanf(argv[2], "%u", &uiKeyLen);
    sscanf(argv[3], "%u", &uiValLen);
    sscanf(argv[4], "%u", &uiNum);
    sscanf(argv[5], "%u", &uiSeed);

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


    RedisHelper redisHelper;
    RedisHelper *pRedisHelper = &redisHelper;

    //Init
    pRedisHelper->Open("10.4.0.5", 6379);

    uint32_t uiTimeDiff;

    //Initialize random seed
    srand(uiSeed);
    char charRandom = (char) (rand() % 26 + 'A');

    TimeDiff::DiffTimeInMicroSecond();
    for (int i = 0; i < iNum; ++i)
    {
        (*pKeyCursorNum)++;
        strInput[i] = strKey;
        pRedisHelper -> Put(strKey, strVal);
    }

    uiTimeDiff = TimeDiff::DiffTimeInMicroSecond();
    cout << ((double) uiTimeDiff) / uiNum / 1000  << " ";

    TimeDiff::DiffTimeInMicroSecond();
    for (int i = 0; i < iNum; ++i)
    {
        string stReturnScore;
        pRedisHelper -> Get(strInput[i], stReturnScore);
    }
    uiTimeDiff = TimeDiff::DiffTimeInMicroSecond();
    cout << ((double) uiTimeDiff) / uiNum / 1000  << "\n";

    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "Finish Test" << endl;

}
