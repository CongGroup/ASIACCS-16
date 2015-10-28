CC=g++
BIN=Ciphertext_throughput Ciphertext_latency Plaintext_cluster_latency Plaintext_cluster_throughput TestGet
#TestAll
FLAGS=-Wall -g -fpermissive -std=c++0x
RM=-rm -f
SRC=$(wildcard *.cpp)
#OBJ=$(SRC:*.cpp=*.o)
OBJ=$(patsubst %.cpp, %.o, $(SRC))
COMMON_OBJ=$(filter-out Ciphertext_throughput.o Ciphertext_latency.o Plaintext_cluster_latency.o Plaintext_cluster_throughput.o TestGet.o,$(OBJ))

#thrift
THRIFT_LINK=-lthrift
THRIFT_LIB=-L/usr/local/lib
THRIFT_INC=-I/usr/local/inc

#openssl
OPENSSL_LINK=-lcrypto

#caravel
CARAVEL_LINK=-lcaravel
CARAVEL_LIB=-L../Caravel
CARAVEL_INC=-I../Caravel

#redis3m
REDIS3M_LINK=-lredis3m 
REDIS3M_LIB=-L/usr/local
REDIS3M_INC=-I/usr/local/include


#combine the inc & lib
INC=$(OPENSSL_INC) $(THRIFT_INC) $(CARAVEL_INC) $(PAILLIER_INC) $(REDIS3M_INC)
LIB=$(CARAVEL_LINK) $(CARAVEL_LIB) $(THRIFT_LINK) $(THRIFT_LIB) $(OPENSSL_LINK) $(REDIS3M_LINK)


all: $(BIN)

%.d: %.cpp
	$(CC) -MM $(FLAGS) $(INC) $< -o $@

%.o: %.cpp %.d
	$(CC) -c $(FLAGS) $(INC) $< -o $@

Ciphertext_throughput:$(OBJ)
	$(CC) $(FLAGS) -o $@ $@.o $(COMMON_OBJ) $(LIB)

Ciphertext_latency:$(OBJ)
	$(CC) $(FLAGS) -o $@ $@.o $(COMMON_OBJ) $(LIB)

Plaintext_cluster_latency:$(OBJ)
	$(CC) $(FLAGS) -o $@ $@.o $(COMMON_OBJ) $(LIB)

Plaintext_cluster_throughput:$(OBJ)
	$(CC) $(FLAGS) -o $@ $@.o $(COMMON_OBJ) $(LIB)

TestGet:$(OBJ)
	$(CC) $(FLAGS) -o $@ $@.o $(COMMON_OBJ) $(LIB)

clean:
	$(RM) *.o
	$(RM) *.d
	$(RM) $(BIN)

-include $(SRC:.cpp=.d)


