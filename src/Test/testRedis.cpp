#include <redis3m/redis3m.hpp>
#include <iostream>

using namespace redis3m;

void Open()
{

}

void Close()
{

}

uint32_t Get(char *pKey, uint32_t uiKeyLen, char *pOut, uint32_t uiOutLen)
{


}

void Put(char *pKey, uint32_t uiKeyLen, char *pVal, uint32_t uiValLen)
{
}


int main(int argc, char **argv)
{
	connection::ptr_t conn = connection::create();
	conn->run(command("SET") << "foo" << "bar" );
	reply r = conn->run(command("GET") << "foo" );
	std::cout << "FOO is: " << r.str() << std::endl;

	char* tkey = "Hello";
	char* tvalue = "world";
	Put(tkey, (unsigned) strlen(*tkey), tvalue, (unsigned) strlen(tvalue));

}
