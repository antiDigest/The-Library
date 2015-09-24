all: library

library: library.cpp
	g++ -g library.cpp

header: header.h
	g++ -g header.h