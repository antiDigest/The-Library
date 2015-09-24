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
#define BOOKS ("books.txt")

#define LOGIN_FAIL "Sorry, those login credentials do not match any !\n\n"
#define LOGIN_ACCEPT "Login credentials accepted !\nWelcome "

class login
{
	string pass;
public:
	string user;
	login(){
		cout<<"Please Login\n";
		printf("Username : ");
		cin>>user;
		pass = getpass("Password : ");
		// cout<<pass;
		if(!check(user,pass)){
			cout<<LOGIN_FAIL;
		}
		cout<<LOGIN_ACCEPT;
	}
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
};

class book{
public:
	book(){
		cout<<"Books managed here !";
	}
	int issue(){
		cout<<"Issued";
	}
	int ret(){
		cout<<"Returned";
	}
	int search(){
		cout<<"Searched";
	}
	~book(){}
};

class library
{
public:
	int value;
	library(){
		login user;
		cout<<user.user;
		while(1){
			cout<<"\n\nThis Software allows you to :\n1. Issue a book.\n2. Return a book.\n3. Search books.\n4. Log Out\n\n";
			cout<<"Select from the above : ";
			cin>>value;
			book book;
			switch(value){
				case 1:
					book.issue();
					break;
				case 2:
					book.ret();
					break;
				case 3:{
					book.search();
					break;
				}
				case 4:{
					exit(0);
				}
				default:
					cout<<"Sorry, wrong input !";
					break;
					
			}	
		}
		
	}
};

int main(){
	printf("\n\n\t\tWelcome to the Library !\n\n");	
	library start;
	printf("\n\n\t   THANK YOU for using the software...\n\n\t\t\tBYE-BYE !\n\n");
	return 0;
}
