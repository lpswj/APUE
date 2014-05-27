//Excerise3.2
//Implementation of dup2 function without call fcntl.
//Date:2014/5/27

#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE 4096
#define OPEN_MAX 256

int dup_2(int fileds,int fileds2);

int main(int argc,char *argv[])
{
	int fd1,fd2,n;
	char buf[BUFFSIZE];

	if(argc != 3){
		printf("Usage:%s fd1 fd2\n",argv[0]);
		return -1;
	}

	fd1 = atoi(argv[1]);
	fd2 = atoi(argv[2]);

	fd1 = dup_2(STDIN_FILENO,fd1);
	fd2 = dup_2(STDOUT_FILENO,fd2);

	printf("STDIN:%d\n",fd1);
	printf("STDOUT:%d\n",fd2);

	while((n = read(fd1,buf,BUFFSIZE)) >0)
	{
		if(write(fd2,buf,n) != n)
			printf("write error!\n");
	}
	if(n < 0)
		printf("read error\n");

	exit(0);
}

int dup_2(int fd1,int fd2)
{
	int fd;

	typedef struct fdlist{
		int fd;
		struct fdlist *next;
	}fd_list;

	fd_list *p,*f1 = NULL;

	if(fd2 < 0 || fd2 > OPEN_MAX)
	{
		err_sys("wrong descriptor");
		return -1;
	}

	if(fd1 == fd2)
		return fd1;

	close(fd2);

	//save the fd until find the exactly one
	//if close fd immediately,fd=dup(fd1) will always the same number
	while((fd = dup(fd1)) != fd2)
	{
		p = (fd_list *)malloc(sizeof(fd_list));
		p->fd = fd;
		p->next = f1;
		f1 = p;
	}

	while(f1 != NULL)
	{
		close(f1->fd);
		p = f1;
		f1 = f1->next;
		free(p);
	}
	return fd;
}
