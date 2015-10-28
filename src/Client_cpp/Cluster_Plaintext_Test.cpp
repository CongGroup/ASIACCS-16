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

int main(int argc, char **argv)
{
    RedisHelper redisHelper;
    RedisHelper *pRedisHelper = &redisHelper;

    //Init
    pRedisHelper->Open("123", 5555);

    uint32_t uiTimeDiff;

    cout << "Begin to basic test ..." << endl;
    cout << "-----------------------------------------------------------------------------" << endl;


    TimeDiff::DiffTimeInMicroSecond();

    pRedisHelper->Put("xxxx", "adfasdf");
    pRedisHelper->Put("xdfxxx", "adfasdf");
    pRedisHelper->Put("xdfxdfxx", "adfasdf");

    uiTimeDiff = TimeDiff::DiffTimeInMicroSecond();

    cout << "Put 2 items cost time : " << uiTimeDiff << endl;

    //Test Get operation
    string strVal;

    TimeDiff::DiffTimeInMicroSecond();

    pRedisHelper->Get("xxxx", strVal);
    pRedisHelper->Put("xdfxxx", strVal);
    pRedisHelper->Put("xdfxdfxx", strVal);

    uiTimeDiff = TimeDiff::DiffTimeInMicroSecond();

    cout << "Get 1 items cost time : " << uiTimeDiff << endl;
    cout << "Xiaoming get score : " << *(uint32_t*)strVal.c_str() << endl;

    //Test GetCol operation
    vector<string> vecVal;

    TimeDiff::DiffTimeInMicroSecond();
    client.GetCol(vecVal, "Test", "Score", 2);
    uiTimeDiff = TimeDiff::DiffTimeInMicroSecond();

    cout << "Test Get Columns which has 2 items cost time : " << uiTimeDiff << endl;
    cout << "Two score are: " << *(uint32_t*)vecVal[0].c_str() << " " << *(uint32_t*)vecVal[1].c_str() << endl;


    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "Finish Test" << endl;

}
