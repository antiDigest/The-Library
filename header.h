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

void add(p *a);

int writefile();

void openfile();

