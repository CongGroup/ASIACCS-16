CC=g++
BIN=CityUScore TestSystem TestScale TestSql
#TestAll
FLAGS=-Wall -g -fpermissive -std=c++0x -O3
RM=-rm -f
SRC=$(wildcard *.cpp)
OBJ=$(SRC:*.cpp=*.o)
COMMON_OBJ=$(filter-out CityUScore.cpp TestSystem.cpp TestAll.cpp TestScale.cpp TestSql.cpp,$(OBJ))

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

CityUScore:$(COMMON_OBJ)
	$(CC) $(FLAGS) -o $@ $@.cpp $(COMMON_OBJ) $(LIB)

TestSystem:$(COMMON_OBJ)
	$(CC) $(FLAGS) -o $@ $@.cpp $(COMMON_OBJ) $(LIB)

#TestAll:$(COMMON_OBJ)
#	$(CC) $(FLAGS) -o $@ $@.cpp $(COMMON_OBJ) $(LIB) $(PAILLIER_LINK) $(PAILLIER_LIB) $(GMP_LINK)

TestScale:$(COMMON_OBJ)
	$(CC) $(FLAGS) -o $@ $@.cpp $(COMMON_OBJ) $(LIB)

TestSql:$(COMMON_OBJ)
	$(CC) $(FLAGS) -o $@ $@.cpp $(COMMON_OBJ) $(LIB)


clean:
	$(RM) *.o
	$(RM) *.d
	$(RM) $(BIN)

-include $(SRC:.cpp=.d)
