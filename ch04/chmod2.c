//Exercise 4.3
//Using chmod to close a file of the read  privilege 
#include "apue.h"

int main(void)
{
	struct stat statbuf;

	/*turn on set-group-ID and turn off group-execute*/
	
	if(stat("bar",&statbuf) < 0)
		err_sys("stat error for foo");
	//Close the read privilege
	if(chmod("bar",(statbuf.st_mode & ~S_IRUSR & ~S_IRGRP & ~ S_IROTH)) < 0)
		err_sys("chmod error for foo");

	exit(0);
}
