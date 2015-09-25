all: library

library: library.cpp
	g++ -g -Wall -I/usr/include/cppconn library.cpp -L/usr/lib -lmysqlcppconn

header: header.h
	g++ -g header.h

# sudo g++  testapp tester.cpp -L/usr/lib -lmysqlcppconn