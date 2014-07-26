#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <termios.h>
#include <unistd.h>
#include "header.h"

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

