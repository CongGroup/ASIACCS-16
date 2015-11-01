#include <iostream>
#include <string.h>
#include <string>
#include <stdint.h>
#include <vector>

#include "DemoConfig.h"
#include "SimConHash.h"
#include "../Caravel/TimeDiff.h"
#include "../Caravel/RedisHelper.h"
#include "../Caravel/Digest.h"

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
        cout << "0 for put. 1 for get. 2 for getCol" << endl;
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
    //[ {OOOO} {XXXXXXXXXXXXXXXXXXXXXXXXXXXXX} ]  {OOOO} means the number;  {XXXX} means the padding for key
    //strKey should not be assign
    uint32_t *pKeyCursorNum;
    pKeyCursorNum = (uint32_t*)(strKey.c_str());
    *pKeyCursorNum = 0;

    //Init strVal	
    string strVal;
    strVal.assign(uiValLen, 'A');

    //Init the client to server

    const uint32_t uiMax = (uint32_t)-1;
    uint32_t uiInterval = uiMax / uiServerNum - 5;

    SimConHash<RedisHelper*> simConHash;

    for (uint32_t uiCur = 0; uiCur < uiServerNum; uiCur++)
    {
        RedisHelper *pRedisHelper = new RedisHelper[uiServerNum];

        pRedisHelper->Open(kDemoServerIP[uiCur], kDemoServerPort[uiCur]);

        //Add a node to SimConHash
        simConHash.InsertNode(uiInterval * (uiCur + 1), pRedisHelper);

    }

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

        string strSha256;
        Digest::Sha256(strKey, strSha256);
        uint32_t *puiSha256 = (uint32_t*)strSha256.c_str();
        uint32_t uiSendKey = puiSha256[0] ^ puiSha256[1] ^ puiSha256[2] ^ puiSha256[3] ^ puiSha256[4] ^ puiSha256[5] ^ puiSha256[6] ^ puiSha256[7];

        RedisHelper *pRedisHelper = *(simConHash.Query(uiSendKey));

        //Put
        if (0 == uiOption)
        {
            pRedisHelper->Put("StudentScoreTable|Score|" + strKey, strVal);
        }
        //Get
        else if (1 == uiOption)
        {
            string stReturnScore;
            pRedisHelper->Get("StudentScoreTable|Score|" + strKey, stReturnScore);
        }
        else
        {
            cout << "ERROR" << endl;
            return 0;
        }


        uiCnt++;
    }

    cout << uiCnt << endl;

    return 0;
}




