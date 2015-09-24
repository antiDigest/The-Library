//LIBRARY
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <termios.h>
#include <unistd.h>
// #include "header.h"
// #include "password.h"

using namespace std;

#define LOGIN_FILE ("login_info.txt")

string user;
string pass;

int check(string name, string pass){
	ifstream file(LOGIN_FILE);

	string line;

	while(getline(file,line)){
		istringstream line_stream(line);
		string user;

		if(!line.find(name)){
			int i=0, flag=0;
			while(getline(line_stream,user,' ')){
				if(i==0 && user.compare(name)==0){
					// cout<<user<<name<<endl;
					flag=1;
				}
				if(i==1 && user.compare(pass)==0 && flag==1){
					// cout<<user<<pass<<endl;
					return 1;
				}
				i++;
			}
		}	
	}
	return 0;
}

int login(){
	printf("Enter Username : ");
	cin>>user;
	pass = getpass("Enter Password : ");
	// cout<<pass;
	if(check(user,pass)){
		return 1;
	}
	return 0;
}

int main(){
	printf("\n\n\t\tWelcome to the Library !\n\n");	
	if(!login()){
		cout<<"Sorry, those login credentials do not match any !\n\n";
	}
	printf("\n\n\t   THANK YOU for using the software...\n\n\t\t\tBYE-BYE !\n\n");
	return 0;
}
