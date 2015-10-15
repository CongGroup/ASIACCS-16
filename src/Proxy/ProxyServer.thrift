/***********************************************************
 * ProxyServer Thrift Script
 * Made By XinyuWang
 * 2015/10/15
 ***********************************************************/

namespace java proxyserver
namespace cpp proxyserver
namespace csharp ProxyServer

//"required" and "optional" keywords are purely for documentation.

service TProxyService {

  /**
   * ProxyGet API
   * @return Value as Binary
   */
  binary ProxyGet(
    1: required binary Trapdoor
  );

  /**
   * ProxyPut API
   */
  void ProxyPut(
    1: required binary Trapdoor,
    2: required binary Val,
	3: required binary IndexTrapdoor,
	4: required binary IndexVal
  );


  /**
   * ProxyGetColumn
   * @return a binary list of Column value
   */
  list<binary> ProxyGetColumn(
    1: required binary IndexTrapdoor,
    2: required binary IndexMask,
	3: required i32 GetNum
  );

  
}
