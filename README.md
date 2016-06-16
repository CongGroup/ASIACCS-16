

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

# REQUIREMENTS

BlindDB is built on Ubuntu 14.04 LTS with gcc version 4.8.4.

This software requires the following libraries:

 * OpenSSL (https://www.openssl.org/source/openssl-1.0.2a.tar.gz)
 * Thrift (http://www.apache.org/dyn/closer.cgi?path=/thrift/0.9.3/thrift-0.9.3.tar.gz)
 * boost C++ library (http://sourceforge.net/projects/boost/files/boost/1.58.0/boost_1_58_0.tar.gz)
 * Redis (http://download.redis.io/releases/redis-3.2.0.tar.gz)
 * Redis3m (https://github.com/luca3m/redis3m)

# INSTALLATION

For linux user, we recommend to fast initialize the experiment server by the following:

 * apt-get update
 * apt-get install gcc g++ libssl-dev libgmp-dev make cmake libboost-dev libboost-test-dev libboost-program-options-dev libboost-system-dev libboost-filesystem-dev libevent-dev automake libtool flex bison pkg-config libglib2.0-dev git
 * apt-get install libmsgpack-dev libboost-thread-dev libboost-date-time-dev libboost-test-dev libboost-filesystem-dev libboost-system-dev libhiredis-dev cmake build-essential libboost-regex-dev

After the initialization, we need to install all required dependencies. First of all, install Thrift by the following:
 
 * wget http://apache.communilink.net/thrift/0.9.3/thrift-0.9.3.tar.gz
 * tar zxvf 
 * cd 
 * make
 * make install

Then, install Redis by the following:

```shell
 * wget http://download.redis.io/releases/redis-3.2.0.tar.gz
 * tar zxvf thrift-0.9.3.tar.gz
 * cd thrift-0.9.3
 * ./configure
 * make
 * make install
 ```

Lastly, install redis3m by the following:

 * git clone https://github.com/luca3m/redis3m
 * cd redis3m
 * cmake .
 * make
 * make install

# CONFIGURATION


 * Configure the Redis
	Start the redis server listening on port 6379.
	
	- redis-server &

 * Configure the Environment
	Add the libraries paths to $LD_LIBRARY_PATH.

	- export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

# MAKE

 After all the above done, let us compile BlindDB by the following:

 * git clone https://github.com/CongGroup/BlindDB
 * cd BlindDB/src
 * make

# EXAMPLE

 * After successful make

	usage: ./CLIENT [filename] [userID] [action] [secutiyType]

	- [filename]: full path of the file;
	- [userID]: user ID of current client;
	- [action]: [-u] upload; [-d] download;
	- [securityType]: [HIGH] AES-256 & SHA-256; [LOW] AES-128 & SHA-1


 * To upload a file "test", assuming from user "0" using AES-256 & SHA-256

	./CLIENT test 0 -u HIGH

 * To download a file "test", assuming from user "1" using AES-128 & SHA-1

	./CLIENT test 1 -d LOW



# MAINTAINER

 * Current maintainer

	- Chuan QIN, the Chinese University of Hong Kong, chintran27@gmail.com

 * Original maintainer

	- Mingqiang Li, Lenovo Hong Kong, mingqianglicn@gmail.com




