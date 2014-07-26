all: Library

Library: Library.c password.c header.h
	gcc -g Library.c password.c
