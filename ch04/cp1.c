//Download version
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>


int IsHoleBlock(char *buf,int len)
{
	int i;
	for(i=0;i<len;i++)
		if(buf[i]!=0)
			return 0;
	return 1;
}

int main(int argc,char *argv[])
{
	int sourcefd,destfd;
	ssize_t nread;
	ssize_t nwrite;
	char *buf;
	size_t len = 1;
	struct stat st;

	if(argc!=3)
	{
		printf("usage: ./a.out <source filename> <destfilename>\n");
		return -1;
	}


	if((sourcefd=open(argv[1],O_RDONLY))<0)
	{
		printf("can't open source file\n");
		return -1;
	}

	if((buf=(char *)malloc(len))==NULL)
	{
		printf("malloc error\n");
		return -1;
	}


	if((destfd=open(argv[2],O_RDWR|O_CREAT|O_TRUNC))<0)
	{
		printf("ceate file error\n");
		return -1;
	}

	while((nread=read(sourcefd,buf,len))>0)
	{
		if(!IsHoleBlock(buf,len))
			if((nwrite=write(destfd,buf,nread))<0)
			{
				printf("write error\n");
				exit(-1);
			}
	}

	if(nread<0)
	{
		printf("read error\n");
		exit(-1);
	}

	free(buf);
	close(sourcefd);
	close(destfd);
	return 0;
}











