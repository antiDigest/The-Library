//LIBRARY
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <termios.h>
#include <unistd.h>
#include "header.h"
#include "password.h"

using namespace std;

int login(){
	char s[50];
	char *pass;
	printf("Enter Username : ");
	cin>>s;
	pass = getpass("Enter Password : ");
	return 0;	
}

int main(){
	printf("\n\n\t\tWelcome to the Library !\n\n");	
	if(!login()){
		printf("\n\n\t   THANK YOU for using the software...\n\n\t\t\tBYE-BYE !\n\n");
		return 0;
	}
	return 0;
}
