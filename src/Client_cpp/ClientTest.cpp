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
	ClientCpp client;
	client.InitKey(DEMO_SECURITY_KEY);
	client.InitExample();
	client.Open();

	uint32_t uiTimeDiff;

	cout << "Begin to basic test ..." << endl;
	cout << "-----------------------------------------------------------------------------" << endl;


	uint32_t uiXiaomingScore = 99;
	uint32_t uiLileiScore = 80;

	TimeDiff::DiffTimeInMicroSecond();

	//Test Put operation
	client.Put("Test", "Xiaoming", "Score", (char*)&uiXiaomingScore, sizeof(uint32_t), true);
	
	client.Put("Test", "Lilei", "Score", (char*)&uiLileiScore, sizeof(uint32_t), true);

	uiTimeDiff = TimeDiff::DiffTimeInMicroSecond();

	cout << "Put 2 items cost time : " << uiTimeDiff << endl;

	//Test Get operation
	string strVal;

	TimeDiff::DiffTimeInMicroSecond();
	client.Get(strVal, "Test", "Xiaoming", "Score");
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
