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
	std::string sKey,sVal;
	sKey.append(pKey);
	reply r = c->run(command("GET") << sKey);
	sVal = r.str();
	uint32_t len = (unsigned) strlen(sVal);
	if (len > uiOutLen)
	{
		return 0;
	}
	else 
	{
//		*pOut = sVal.c_str();	
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
	return;
}


int main(int argc, char **argv)
{
	//connection::ptr_t conn = connection::create();
	//conn->run(command("SET") << "foo" << "bar" );
	Open();
	char* tkey = "Hello";
	char* tvalue = "world";
	Put(tkey, (unsigned) sizeof(*tkey), tvalue, (unsigned) sizeof(tvalue));
	
	// reply r = c->run(command("GET") << "Hello" );
	// std::cout << "Hello is: " << r.str() << std::endl;

}
