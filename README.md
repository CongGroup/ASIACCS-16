

# BlindDB

 * Introduction
 * Requirements
 * Installation
 * Configuration
 * Make
 * Example
 * Maintainers

# INTRODUCTION

BlindDB is an encrypted, distributed, and searchable key-value store. It achieves strong protection on data privacy while preserving prominent features of plaintext NoSQL key-value stores. BlindDB is built on a secure data partition algorithm that distributes encrypted data evenly across a cluster of nodes. It also supports multiple data models in a privacy-preserving way. Currently, two basic APIs PUT/GET are implemented. To enable secure queries for encrypted secondary attributes of data, BlindDB provides searchable symmetric encryption based encrypted secondary indexes which consider security, efficiency, and data locality simultaneously. In this prototype, Redis is used as the underlying key-value store, and the column oriented data model is supported for a proof of concept.

# REQUIREMENTS

BlindDB is built on Ubuntu 14.04 LTS with gcc version 4.8.4.

This software requires the following libraries:

 * OpenSSL (https://www.openssl.org/source/openssl-1.0.2a.tar.gz)
 * Thrift (http://www.apache.org/dyn/closer.cgi?path=/thrift/0.9.3/thrift-0.9.3.tar.gz)
 * boost C++ library (http://sourceforge.net/projects/boost/files/boost/1.58.0/boost_1_58_0.tar.gz)
 * LevelDB (http://download.redis.io/releases/redis-3.2.0.tar.gz)

# INSTALLATION

For linux user, we recommend to fast initialize the experiment server by the following:

 * sudo apt-get update
 * sudo apt-get install gcc g++ libssl-dev libgmp-dev make cmake libboost-dev libboost-test-dev libboost-program-options-dev libboost-system-dev libboost-filesystem-dev libevent-dev automake libtool flex bison pkg-config libglib2.0-dev

After the initialization, we need to install all required dependencies. First of all, install Thrift by the following:
 
 * 

# CONFIGURATION


 * Configure the server (CDStore requires at least 4 storage server)

	- Make sure there are three directories under /server/meta
	- "DedupDB" for levelDB logs
	- "RecipeFiles" for temp recipe files
	- "ShareContainers" for share local cache
	- Start a server by "./SERVER [port]"

 * Configure the client

	- In the configure file /client/config, specify the storage nodes line by line with [IP]:[port]

	Example: you have run 4 servers with "./SERVER [port]" on machines:
		- 192.168.0.30 with port 11030
		- 192.168.0.31 with port 11031
		- 192.168.0.32 with port 11032
		- 192.168.0.33 with port 11033
		
		you need to specify the ip and port in config with following format: 

			192.168.0.30:11030
			192.168.0.31:11031
			192.168.0.32:11032
			192.168.0.33:11033

		(the actual order doesn't matter)
	
	- (Optional) In the configure class of client, /client/util/conf.hh

		- set chunk and secure parameters following the comments
		- set the number of storage nodes according to your running servers

# MAKE


	To make a client, on the client machine:

	 * Go to /client/lib/, type "make" to make gf_complete
	 * Back to /client/, type "make" to get the executable CLIENT program

	To make a server, on each storage node:

	 * Go to /server/lib/leveldb/, type "make" to make levelDB
	 * Back to /server/, type "make" to get the executable SERVER program



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




