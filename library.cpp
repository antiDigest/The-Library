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

#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"

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
			cout << RED << LOGIN_FAIL << NRM;
			exit(0);
		}
		cout << GRN << LOGIN_ACCEPT << NRM;
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
		// cout<<"Books managed here !\n";
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
				
				if(issued!="1"){
					cout << "\nDo you want to issue this book ?(y/n) : ";
					cin >> enter;
					if(enter=='y'){
						ostringstream strstr;
						strstr << "UPDATE Books SET Issued='1' where Books.name='" << bookname << "'";
						string str = strstr.str();
						stmt->executeQuery(str);
						cout << BLU << "Book Issued !" << NRM;
						flag=1;
					}
				}					
				else{
					cout << RED << "\nBook has already been issued to someone else" << NRM;
					flag=0;
					continue;
				}
			}
			if(flag==1)
				break;
		}
	}
	void ret(){
		string bookname;
		string issued;
		char enter;
		int flag=0;
		cout<<"Enter a book : ";
		cin>>name;
		res = stmt->executeQuery("SELECT * from userbooks"); // replace with your statement
		while (res->next()) {
			/*string book_id = res->getString("book_id");
			string user_id = res->getString("user_id");
			ostringstream strstr;
			strstr << "SELECT * from Books WHERE book_id='" << book_id << "'";
			string str = strstr.str();
			book = stmt->executeQuery(str);
			ostringstream strstr;
			strstr << "SELECT * from login WHERE user_id='" << user_id << "'";
			string str = strstr.str();
			user = stmt->executeQuery(str);*/
			if(bookname.find(name)==0){
				cout << bookname;
				if(issued=="1"){
					cout << "\nDo you want to return this book ?(y/n) : ";
					cin >> enter;	
					if(enter=='y'){
						ostringstream strstr;
						strstr << "UPDATE Books SET Issued='1' where Books.name='" << bookname << "'";
						string str = strstr.str();
						stmt->execute(str);
						cout << GRN << "Book Issued !" << NRM;
						flag=1;
					}
				}					
				else{
					cout << RED << "\nBook has not been issued to you" << NRM;
					flag=0;
					continue;
				}
			}
			if(flag==1)
				break;
		}
	}
	void search(){
		string bookname;
		cout<<"Enter a keyword : ";
		cin>>name;
		res = stmt->executeQuery("SELECT * from userbooks"); // replace with your statement
		while (res->next()) {
			bookname = res->getString("name");
			if(bookname.find(name)==0){
				cout << bookname;
			}
		}
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
			cout<<"Select from the above : " << BLU	<< BLU;
			cin>>value;
			cout << NRM;
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
					printf("\n\n\t   THANK YOU for using the software...\n\n\t\t\tBYE-BYE !\n\n");
					exit(0);
				}
				default:
					cout<<RED<<"Sorry, wrong input !"<<NRM;
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


	
	return 0;
}
