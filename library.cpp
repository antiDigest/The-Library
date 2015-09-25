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
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

#define LOGIN_FILE ("login_info.txt")
#define BOOKS ("books.txt")

#define LOGIN_FAIL "Sorry, those login credentials do not match any !\n\n"
#define LOGIN_ACCEPT "Login credentials accepted !\nWelcome "

sql::Connection *con;

class login
{
	string pass;
public:
	string user;
	sql::Statement *stmt;
	sql::ResultSet *res;
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
		int flag = 0;
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * from login"); // replace with your statement
		while (res->next()) {
			if(name.compare(res->getString("username"))==0 && pass.compare(res->getString("password"))==0){
				flag =1;
				break;
			}
		}
		if (flag==1){
			return 1;
		}
		return 0;
	}
};

class book{
public:
	string name;
	sql::Statement *stmt;
	sql::ResultSet *res;

	book(){
		cout<<"Books managed here !\n";
		stmt = con->createStatement();
		
	}
	void issue(){
		string bookname;
		string issued;
		char enter;
		int flag=0;
		cout<<"Enter a book : ";
		cin>>name;
		res = stmt->executeQuery("SELECT * from Books"); // replace with your statement
		while (res->next()) {
			bookname = res->getString("name");
			issued = res->getString("Issued");
			if(bookname.find(name)==0){
				cout << bookname;
				cout << "Do you want to issue this book ?(y/n) : ";
				cin >> enter;
				if(issued!="1"){
					if(enter=='y'){
						sql::Statement *query;
						query->executeQuery("UPDATE Books SET Issued='1' where Books.name='%s' ",bookname);
						delete query;
						flag=1;
					}
				}					
				else{
					cout<<"Book has already been issued to someone else";
					flag=0;
				}
			}
			if(flag==1)
				break;
		}
	}
	void ret(){
		cout<<"Returned";
	}
	void search(){
		cout<<"Searched";
	}
	~book(){
		delete res;
		delete stmt;
	}
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
	try {
		sql::Driver *driver;

		/* Create a connection */
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "tribble");
		con->setSchema("library"); // connect with database

		library start;

		delete con;
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}


	printf("\n\n\t   THANK YOU for using the software...\n\n\t\t\tBYE-BYE !\n\n");
	return 0;
}
