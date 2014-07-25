//LIBRARY

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <termios.h>
#include <unistd.h>


typedef struct password_list{
	char *username;
	char *password;
	struct password_list *ptr;
}p;

typedef struct database_list{
	char *user;
	char *book;
	struct database_list *link;
}d;

p *first;
d *start;

void add(p *a){
	//printf("hello");
	p *temp;
	first->ptr=NULL;
	//temp=(p*)malloc(sizeof(p));
	//printf("\n\nIn add");
	__fpurge(stdin);
	if (first->username==NULL && first->password==NULL){
		first->username=a->username;
		first->password=a->password;
		first->ptr=NULL;
		//printf("\n\n%s : %s\n\n",first->username,first->password);
	}
	else{
		temp=first;
		printf("\n\t%s : %s\n",temp->username,temp->password);
		while(temp->ptr!=NULL){
			printf("\nHELLO WORLD\n");
			printf("\n\t%s : %s\n",temp->username,temp->password);
			temp=temp->ptr;
			
		}
		temp=a;
		temp->ptr = NULL;
		//printf("\n%s :: %s\n",temp->username,temp->password);
	}
	//writefile();
	return;
}

writefile(){
	FILE *f;
	char *s;
	int i;
	p *a;
	printf("\nIn writefile\n");
	s=(char*)malloc(sizeof(char)*50);
	//s=NULL;
	a=(p*)malloc(sizeof(p));
	f=fopen("password1.txt","w");
	printf("hello");
	a=first;
	while(a->ptr!=NULL){
		//fprintf(f,"%s\t%s",a->username,a->password);
		printf("%s\t%s",a->username,a->password);
		a=a->ptr;
	}
	fclose(f);
}

void openfile(){
	FILE *f;
	char *s1,*s2;
	int i;
	p *a;
	s1=(char*)malloc(sizeof(char)*50);
	s2=(char*)malloc(sizeof(char)*50);
	//s1=NULL;
	a=(p*)malloc(sizeof(p));
	f=fopen("password.txt","r");
	__fpurge(stdin);
	while(!feof(f)){
		//printf("Not printing here");
		fscanf(f,"%s\t%s",s1,s2);
		if (s1==NULL)
		{
			printf("\nNo user data Exists... \n\n");
		}
		a->username=s1;
		//printf("%s\n",a->username);
		//fscanf(f,"%s",s);
		a->password=s2;
		//printf("%s\n",a->username);
		//printf("%s\n",a->password);
		add(a);
	}
	fclose(f);
}

int check(char s[], char *pass){
	char c;
	int flag=0;
	p *a;
	openfile();
	a=first;
	while(a->ptr!=NULL){
		printf("\n\n%s\t%s\n\n",a->username,a->password);
		if(a->username==s && a->password==pass){
			flag=1;
		}
		a=a->ptr;
	}
	if (flag==0){
		printf("You have not been signed up... Wanna sign up ?(Y/n) : ");
		scanf("%c",&c);
		if(c=='Y'){
			if(signup(0)==-1){
				return -1;
			}
		}
		else{
			return -1;
		}
	}
}

int signup(int n){
	char *s;
	p *a;
	char *pass;
	char *repass;
	a=(p*)malloc(sizeof(p));
	__fpurge(stdin);
	printf("Enter Username : ");
	scanf("%s",s);
	//printf("Enter Password : ");
	pass = getpass("Enter Password : ");
	repass = getpass("Re-enter Password : ");
	if(strcmp(pass,repass)==0){
		a->username=s;
		a->password=repass;
		add(a);
	}
	else if(n<3){
		printf("Passwords do not match...\n\n");
		signup(n+1);
		//return -1;
	}
	else{
		return -1;
	}
	return;
}

int database(){
	printf("Database here");
}

int login(){
	char s[50];
	char *pass;
	__fpurge(stdin);
	printf("Enter Username : ");
	fgets(s,50, stdin);
	pass = getpass("Enter Password : ");
	//printf("%s\n",s);
	//printf("%s\n\n",pass);
	if (check(s,pass)==-1){
		return -1;
	}
}

void main(){
	first=(p*)malloc(sizeof(p));
	first->username=NULL;
	first->password=NULL;
	start=(d*)malloc(sizeof(d));
	start->user=NULL;
	start->book=NULL;
	printf("\n\n\t\tWelcome to the Library !\n\n");	
	if(login()==-1){
		printf("\n\n\t   THANK YOU for using the software...\n\n\t\t\tBYE-BYE !\n\n");
		return;
	}
	if(database()==-1){
		printf("\n\n\t   THANK YOU for using the software...\n\n\t\t\tBYE-BYE !\n\n");
		return;
	}
	return;
}
