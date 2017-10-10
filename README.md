

# BlindDB

 * Introduction
 * Requirements
 * Installation
 * Configuration
 * Make
 * Example
 * Maintainers

# INTRODUCTION

BlindDB is an encrypted, distributed, and searchable key-value store. It achieves strong protection on data privacy while preserving prominent features of plaintext NoSQL key-value stores. BlindDB is built on a secure data partition algorithm that distributes encrypted data evenly across a cluster of nodes. It also supports multiple data models in a privacy-preserving way. Currently, two basic operations PUT/GET are implemented. To enable secure queries for encrypted secondary attributes of data, BlindDB provides searchable symmetric encryption based encrypted secondary indexes which consider security, efficiency, and data locality simultaneously. In this prototype, Redis is used as the underlying key-value store, and the column oriented data model is supported for a proof of concept.

# PUBLICATION

Xingliang Yuan, Xinyu Wang, Cong Wang, Chen Qian, and Jianxiong Lin, "Building an Encrypted, Distributed, and Searchable Key-value Store", In the 11th ACM Asia Conference on Computer and Communications Security (AISACCS'16).

# REQUIREMENTS

Recommended environment: Ubuntu 14.04 LTS with gcc version 4.8.4.

This software requires the following libraries:

 * OpenSSL (https://www.openssl.org/source/openssl-1.0.2a.tar.gz)
 * Thrift (http://www.apache.org/dyn/closer.cgi?path=/thrift/0.9.3/thrift-0.9.3.tar.gz)
 * boost C++ library (http://sourceforge.net/projects/boost/files/boost/1.58.0/boost_1_58_0.tar.gz)
 * Redis (http://download.redis.io/releases/redis-3.2.0.tar.gz)
 * Redis3m (https://github.com/luca3m/redis3m)

# INSTALLATION

Environment setup:

```shell
 * apt-get update
 * apt-get install gcc g++ libssl-dev libgmp-dev make cmake libboost-dev libboost-test-dev libboost-program-options-dev libboost-system-dev libboost-filesystem-dev libevent-dev automake libtool flex bison pkg-config libglib2.0-dev git
 * apt-get install libmsgpack-dev libboost-thread-dev libboost-date-time-dev libboost-test-dev libboost-filesystem-dev libboost-system-dev libhiredis-dev cmake build-essential libboost-regex-dev
```

Thrift installation:
 
```shell
 * wget http://apache.communilink.net/thrift/0.9.3/thrift-0.9.3.tar.gz
 * tar zxvf 
 * cd 
 * make
 * make install
```

Redis installation:

```shell
 * wget http://download.redis.io/releases/redis-3.2.0.tar.gz
 * tar zxvf redis-3.2.0.tar.gz
 * cd redis-3.2.0
 * make
 * make install
 ```

redis3m (a C++ Redis client) installation:

```shell
 * git clone https://github.com/luca3m/redis3m
 * cd redis3m
 * cmake .
 * make
 * make install
```

# CONFIGURATION


 * Configure the Redis
	Start the redis server listening on port 6379.

	```shell
	* redis-server &
	```

 * Configure the environment
	Add the libraries paths to $LD_LIBRARY_PATH.

	```shell
	* export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
	```
 * Configure IPs and Ports
	Input IP and PORT of each machine to an configuration file in /BlindDB/src/Client/DemoConfig.h

	```cpp
	#define DEMO_SECURITY_KEY "adfaksdfjklasdjflajsdiofjasodf"
	const std::string kDemoServerIP[] = { "10.4.0.5", "10.4.0.6", "10.4.0.9", "10.4.0.10", "10.4.0.11", "10.4.0.12", "10.4.0.13", "10.4.0.14", "10.4.0.15", "10.4.0.16" };
	const uint16_t kDemoServerPort[] = { 9090, 9090, 9090, 9090, 9090, 9090, 9090, 9090, 9090, 9090 };
	const uint16_t kRedisPort[] = { 6379, 6379, 6379, 6379, 6379, 6379, 6379, 6379, 6379, 6379 };

	```

# MAKE

 Compile BlindDB:

```shell
 * git clone https://github.com/CongGroup/BlindDB
 * cd BlindDB/src
 * make
```

# EXAMPLE

  * TestPT.sh
	
	Scripts that generate plaintext workloads


	```
	Usage : /BlindDB/src/Client/TestPT.sh [NodeNum] [LOOP] [OPTION] [TIME] [SEEDS]

	- [NodeNum]: the number of nodes.
	- [LOOP]: the number of clients.
	- [OPTION]: "0" put only workload, "1" get only workload, "2" get heavy workload, "3" put heavy workload.
	- [TIME]: time duration for the workload.
	- [SEEDS]: random seed.
	```


  * TestCT.sh
	
	Scripts that generate ciphertext workloads


	```
	Usage : /BlindDB/src/Client/TestCT.sh [NodeNum] [LOOP] [OPTION] [TIME] [SEEDS]

	- [NodeNum]: the number of nodes.
	- [LOOP]: the number of clients.
	- [OPTION]: "0" put only workload, "1" get only workload, "2" get heavy workload, "3" put heavy workload.
	- [TIME]: time duration for the workload.
	- [SEEDS]:  random seed.
	```


  * Ciphertext Latency

	Test the latency of secure PUT/GET operations


	```
	Usage : /BlindDB/src/Client/Ciphertext_latency [DataNodeNum] [KeyLen] [ValLen] [Times]

	- [DataNodeNum]: the number of nodes.
	- [KeyLen]: the length of key in bytes.
	- [ValLen]: the length of value in bytes.
	- [Times]: times of operations.
	```


  * Plaintext Cluster Latency

	Test the latency of PUT/GET operations 


	```
	Usage : /BlindDB/src/Client/Plaintext_cluster_latency [DataNodeNum] [KeyLen] [ValLen] [Times]

	- [DataNodeNum]: the number of nodes.
	- [KeyLen]: the length of key in bytes.
	- [ValLen]: the length of value in bytes.
	- [Times]: times of operations.
	```

# MAINTAINER

 * Current maintainer

	- Xinyu Wang, City University of Hong Kong, xy.w@my.cityu.edu.hk
	- Xingliang Yuan, City University of Hong Kong, xl.y@my.cityu.edu.hk
	- Cong Wang, City University of Hong Kong, congwang@cityu.edu.hk
	
 * Prior team member
 	
	- Jianxiong Lin
	- Yilei Chu



