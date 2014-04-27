//	The LIBRARY !

#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   

#define SIZE 100

typedef struct book
{
	char usrname[20];
	char book[50];
	struct book *ptr;
}b;

typedef struct usrnm
{
	char usr[20];
	char pass[20];
	struct usrnm *link;
}u;

b *start;
u *first;

void fileget()
{
	FILE *p;
	b *a,*t;
	a=(b*)malloc(sizeof(b));
	start=NULL;
	t=start;
	p=fopen("database.txt","w+");
	while(feof(p))
	{
		fscanf(p,"\t%s\t%s\n",a->usrname,a->book);
		a->ptr=NULL;
		if(start==NULL) {
			a=start;
		} else {
			while(t->ptr!=NULL) {
				t=t->ptr;
			}
			t->ptr=a;
		}
		printf("\t%a\t%s\n",a->usrname,a->book);
	}
	fclose(p);
}

u* filegetpass()
{
	FILE *p;
	u *a;
	a=first;
	p=fopen("password.txt","r+");
	__fpurge(stdin);
	//fflush(stdin);
	while(feof(p))
	{
		if(first==NULL)
		{
			printf("a");
			fscanf(p,"\t%s\t%s",first->usr,first->pass);
			first->link=NULL;
			a=first;
		}
		printf("a");
		fscanf(p,"\t%s\t%s",a->usr,a->pass);
		a->link=NULL;
		a=a->link;	
	}
	printf("Done");
	a=first;
	while(a->link!=NULL)
	{
		printf("\t%s\t%s\n",a->usr,a->pass);
		a=a->link;
	}
	fclose(p);
	return first;
}

void getPassword(char password[])
{
    static struct termios oldt, newt;
    int i = 0;
    int c;
    __fpurge(stdin);
    //fflush(stdin);
    /*saving the old settings of STDIN_FILENO and copy settings for resetting*/
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    /*setting the approriate bit in the termios struct*/
    newt.c_lflag &= ~(ECHO);          
    /*setting the new bits*/
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
    /*reading the password from the console*/
    fflush(stdin);
    while ((c = getchar())!= '\n' && c != EOF && i < SIZE){
        password[i++] = c;
    }
   	password[i] = '\0';
    /* resetting our old STDIN_FILENO */ 
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    return;
}

u* check()
{
	u *a, *t;
	char ch, copy[20];
	a=(u*)malloc(sizeof(u));
	t=(u*)malloc(sizeof(u));
	int i;
	t=first;
	__fpurge(stdin);
	//fflush(stdin);
	if(first==NULL)
	{		
		printf("\n\t::No users entered yet::\n\n");
		printf("Sign Up? (y/n): ");
		__fpurge(stdin);
		//fflush(stdin);
		scanf("%c",&ch);
		if(ch=='y')
			user();
		else
		{
			exit(0);
		}
		check();
	}
	else
	{
		i=0;
		printf("Username: ");
		scanf("%d",a->usr);
		printf("Password: ");
		getPassword(a->pass);
		while(t!=NULL)
		{
			if(t->usr==a->usr && t->pass==a->pass)
			{
				printf("\n::Welcome %s::\n",a->usr);
				return a;
			}
			t=t->link;
		}
		printf("\n::Wrong Username OR Password::\n");
		return a;
	}
}

b* addbk()
{
	b *a, *t, *s;
	u *z;
	FILE *file;
	file=fopen("database.txt","w");
	char copy[50];
	a=(b*)malloc(sizeof(b));
	t=(b*)malloc(sizeof(b));
	z=(u*)malloc(sizeof(u));
	t=start;
	a=NULL;
	z = check();
	__fpurge(stdin);
	//fflush(stdin);
	strcpy(a->usrname,z->usr);
	if(a->usrname!=NULL)
	{
		__fpurge(stdin);
		//fflush(stdin);
		printf("Enter your book: ");
		scanf("%s",a->book);
		while(t->ptr!=NULL)
		{
			if(t==start)
			{
				start=a;
				start->ptr=NULL;
			}
			else if(t==start->ptr)
			{
				if(start->ptr==t->ptr)
				{
					start->ptr=a;
					a->ptr=t;
					t->ptr=NULL;
				}
				else
				{
					t->ptr=a;
					t->ptr->ptr=NULL;
				}
			}
			else
			{
				if(strcmp(a->usrname,t->usrname)==0 && strcmp(a->usrname,t->ptr->usrname)>0)
				{
					a->ptr=t->ptr;
					t->ptr=a;
				}
				else if(strcmp(a->usrname, t->usrname)>0 && strcmp(a->usrname, t->ptr->usrname)<0)
				{
					a->ptr=t->ptr;
					t->ptr=a;
				}
			}
			fprintf(file,"\t%s\t%s\n",t->usrname,t->book);
			t=t->ptr;
		}
	}
	else
	{
		printf("\n\tUser making failed !\n");
	}
	fclose(file);
	return;
}

b* rembk()
{
	b *a, *t;
	u *z;
	FILE *file;
	a=(b*)malloc(sizeof(b));
	t=(b*)malloc(sizeof(b));
	z=(u*)malloc(sizeof(u));
	t=start;
	a=NULL;
	file=fopen("database.txt","w");
	z=check();
	__fpurge(stdin);
	//fflush(stdin);
	strcpy(a->usrname,z->usr);
	if(a->usrname!=NULL)
	{
		printf("Enter book to be removed: ");
		scanf("%s",a->book);
		while(t!=NULL)
		{
			if(strcmp(a->usrname,t->ptr->usrname)==0 && strcmp(a->book, t->ptr->book)==0)
			{
				printf("Removed: %s from user %s",t->ptr->book,t->ptr->usrname);
				t->ptr=t->ptr->ptr;
			}
			fprintf(file,"\t%s\t%s\n",t->usrname,t->book);
			t=t->ptr;
		}
	}
	fclose(file);
}

b* searchbk()
{
	b *t;
	char a[50];
	t=(b*)malloc(sizeof(b));
	t=start;
	__fpurge(stdin);
	//fflush(stdin);
	printf("Enter book to be searched: ");
	scanf("%s",a);
	while(t->ptr!=NULL)
	{
		if(strcmp(a,t->ptr->book)==0)
		{
			printf("Book: %s with %s",t->ptr->book,t->ptr->usrname);
		}
		t=t->ptr;
	}
	return 0;
}

void display()
{
	b *t;
	t=start;
	__fpurge(stdin);
	//fflush(stdin);
	printf("\tUsername\tBook\n");
	while(t!=NULL)
	{
		printf("\t%s\t%s\n",t->usrname, t->book);
		t=t->ptr;
	}
}

int user()
{
	FILE *file;
	u *a, *t;
	char passwd[50];
	__fpurge(stdin);
	//fflush(stdin);
	a=(u*)malloc(sizeof(u));
	t=(u*)malloc(sizeof(u));	
	file=fopen("password.txt","a");
	printf("Enter Username: ");
	scanf("%s",a->usr);
	printf("Enter Password: ");
	getPassword(a->pass);
	printf("\nConfirm Password: ");
	getPassword(passwd);
	first=filegetpass();
	if(strcmp(a->pass,passwd)!=0)
	{
		printf("\n\nPasswords Do Not Match!\n\n");
		user();
	}
	else 
	{
		printf("\n\n\t::Welcome %s::\n\n",a->usr);
		if(first==NULL)
		{
			first=a;
			first->link=NULL;
			fprintf(file,"\t%s\t%s\n",first->usr,first->pass);
			printf("\t::Succesfully Added::\n");
		}
		else
		{
			t=first;
			while(t->link!=NULL)
			{t=t->link;}
			t->link=a;
			t->link=NULL;
			fprintf(file,"\t%s\t%s\n",t->usr,t->pass);
			printf("\t::Succesfully Added Again::\n");
		}
	}
	fclose(file);
	return 0;
}

void main ()
{
	int n;
	first=(u*)malloc(sizeof(u));
	start=(b*)malloc(sizeof(b));
	first=NULL;
	while(1)
	{
		printf("\n1. Add book\n2. Remove a book\n3. Search for a book\n4. New User\n5. Display Users with their Books.\n6. Exit\n");
		printf("\nEnter Your Choice: ");
		scanf("%d",&n);
		switch(n)
		{
			case 1:
				addbk();
				break;
			case 2:
				rembk();
				break;
			case 3:
				searchbk();
				break;
			case 4:
				user();
				break;
			case 5:
				display();
				break;
			case 6:
				exit(0);
				break;
			default:
				printf("\n\nI am sorry... No action to be performed at this input!\n");
		}
	}
}
