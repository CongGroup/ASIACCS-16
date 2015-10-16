CC=g++
BIN=ProxyServer_types ProxyServer_constants RedisHelper TProxyService
#TestAll
FLAGS=-Wall -g -fpermissive -std=c++0x -O3
RM=-rm -f
SRC=$(wildcard *.cpp)
#OBJ=$(SRC:*.cpp=*.o)
OBj=$(patsubst %.cpp, %.o, $(SRC))
COMMON_OBJ=$(filter-out ProxyServer_types.o ProxyServer_constants.o RedisHelper.o TProxyService.o,$(OBJ))

#thrift
THRIFT_LINK=-lthrift
THRIFT_LIB=-L/usr/local/lib

#openssl
OPENSSL_LINK=-lcrypto

#caravel
CARAVEL_LINK=-lcaravel
CARAVEL_LIB=-L../Caravel
CARAVEL_INC=-I../Caravel

#GMP
GMP_LINK=-lgmp

#paillier
PAILLIER_LINK=-lpaillier
PAILLIER_INC=-I/usr/local/include
PAILLIER_LIB=-L/usr/local/lib

#combine the inc & lib
INC=$(OPENSSL_INC) $(THRIFT_INC) $(CARAVEL_INC) $(PAILLIER_INC)
LIB=$(CARAVEL_LINK) $(CARAVEL_LIB) $(THRIFT_LINK) $(THRIFT_LIB) $(OPENSSL_LINK) 


all: $(BIN)

%.d: %.cpp
	$(CC) -MM $(FLAGS) $(INC) $< -o $@

%.o: %.cpp %.d
	$(CC) -c $(FLAGS) $(INC) $< -o $@

ProxyServer_types:$(COMMON_OBJ)
	$(CC) $(FLAGS) -o $@ $@.cpp $(COMMON_OBJ) $(LIB)

ProxyServer_constants:$(COMMON_OBJ)
	$(CC) $(FLAGS) -o $@ $@.cpp $(COMMON_OBJ) $(LIB)

#TestAll:$(COMMON_OBJ)
#	$(CC) $(FLAGS) -o $@ $@.cpp $(COMMON_OBJ) $(LIB) $(PAILLIER_LINK) $(PAILLIER_LIB) $(GMP_LINK)

RedisHelper:$(COMMON_OBJ)
	$(CC) $(FLAGS) -o $@ $@.cpp $(COMMON_OBJ) $(LIB) `pkg-config --cflags --libs redis3m`

TProxyService:$(COMMON_OBJ)
	$(CC) $(FLAGS) -o $@ $@.cpp $(COMMON_OBJ) $(LIB)


clean:
	$(RM) *.o
	$(RM) *.d
	$(RM) $(BIN)

-include $(SRC:.cpp=.d)
