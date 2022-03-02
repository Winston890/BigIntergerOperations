#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#  make                makes Shuffle
#  make ListClient     make ListClient
#  make clean          removes binary files
#  make check1         runs valgrind on ListClient
#  make check2         runs valgrind on Shuffle with CLA 35
#------------------------------------------------------------------------------

all: Arithmetic BigIntegerTest ListTest 


Arithmetic : BigInteger.o List.o Arithmetic.o
	g++ -std=c++17 -Wall -o Arithmetic Arithmetic.o BigInteger.o List.o

BigIntegerTest : BigIntegerTest.o BigInteger.o List.o
	g++ -std=c++17 -Wall -o BigIntegerTest BigIntegerTest.o BigInteger.o List.o

ListTest : ListTest.o List.o
	g++ -std=c++17 -Wall -o ListTest ListTest.o List.o 

Arithmetic.o : Arithmetic.cpp BigInteger.h List.h
	g++ -std=c++17 -Wall -c Arithmetic.cpp

ListTest.o : List.h ListTest.cpp
	g++ -std=c++17 -Wall -c ListTest.cpp

List.o : List.h List.cpp
	g++ -std=c++17 -Wall -c List.cpp

BigInteger.o : BigInteger.h BigInteger.cpp List.cpp
	g++ -std=c++17 -Wall -c BigInteger.cpp List.cpp

clean :
	rm -f Arithmetic Arithmetic.o BigIntegerTest BigIntegerTest.o BigInteger.o ListTest ListTest.o List.o
