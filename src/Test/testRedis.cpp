#include <redis3m/redis3m.hpp>
#include <iostream>
#include <cstring>

using namespace redis3m;
connection::ptr_t c;
void Open()
{
	c = connection::create();
}

void Close()
{

}

uint32_t Get(char *pKey, uint32_t uiKeyLen, char *pOut, uint32_t uiOutLen)
{
	uint32_t len = 0;
	std::string sKey,sVal;
	sKey.append(pKey);
	reply r = c->run(command("GET") << sKey);
	sVal = r.str();

	len = (unsigned) sVal.size();
	if (len > uiOutLen)
	{
		return 0;
	}
	else 
	{
		strcpy(pOut, sVal.c_str());
		return len;
	}
}

void Put(char *pKey, uint32_t uiKeyLen, char *pVal, uint32_t uiValLen)
{	
	std::string sKey,sVal;
	sKey.append(pKey);
	sVal.append(pVal);
        //std::cout << sKey << " " << sVal;
	c->run(command("SET") << sKey << sVal);
	std::cout << uiKeyLen << " " << uiValLen << std::endl;
	return;
}


int main(int argc, char **argv)
{
	//connection::ptr_t conn = connection::create();
	//conn->run(command("SET") << "foo" << "bar" );
	Open();
	char* tkey = "Hi";
	char* tvalue = "Redis";
	Put(tkey, (unsigned) 2, tvalue, (unsigned) 5);
	char* rvalue;
	uint32_t uiOutLen = 1000;
	std::cout << Get("Hi", 2, rvalue, uiOutLen) << std::endl;
	std::cout << *rvalue << std::endl;
	// reply r = c->run(command("GET") << "Hello" );
	// std::cout << "Hello is: " << r.str() << std::endl;

}
