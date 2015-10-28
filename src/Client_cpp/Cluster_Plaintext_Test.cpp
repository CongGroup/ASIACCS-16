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
    RedisHelper redisHelper;
    RedisHelper *pRedisHelper = &redisHelper;

    //Init
    pRedisHelper->Open("10.4.0.7", 6379);

    uint32_t uiTimeDiff;

    cout << "Begin to basic test ..." << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

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
