//Exercise 4.6
//A program similar with cp(1),which copy files included file hole
//but it don't output the zero byte.

#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE 4096

int main(int argc,char *argv[])
{
	int n;
	int file1,file2;
	char buf[BUFFSIZE];

	if(argc != 3)
		err_sys("%s: file1 file2",argv[0]);

	if((file1 = open(argv[1],O_RDONLY)) < 0)
		err_sys("%s open failed",argv[1]);

	if((file2 = open(argv[2],O_CREAT|O_EXCL|O_RDWR)) <0)
		err_sys("%s open failed",argv[2]);

	while((n = read(file1,buf,BUFFSIZE)) > 0){
			if(strcmp(buf,"") == 0)
				continue;
			if(write(file2,buf,n) != n)
				err_sys("wrtie error");
			}

	if(n < 0)
		err_sys("read error");
	return 0;
}
