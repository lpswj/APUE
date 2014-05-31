//exercise4.1 
//Using stat insted of lstat
#include "apue.h"


int main(int argc,char *argv[])
{
	int i;
	struct stat buf;
	char *ptr;

	for(i=1;i < argc;i++){
		printf("%s: ",argv[i]);
		if(stat(argv[i],&buf) < 0){
			err_ret("stat error");
			continue;
		}
		if(S_ISREG(buf.st_mode))
			ptr = "regular";
		else if(S_ISDIR(buf.st_mode))
			ptr = "directory";
		else if(S_ISCHR(buf.st_mode))
			ptr = "character special";
		//stat follow the link
		else if(S_ISBLK(buf.st_mode))
			ptr = "block special";
		else if(S_ISFIFO(buf.st_mode))
			ptr = "fifo";
		else if(S_ISLNK(buf.st_mode))
			ptr = "symbolic link";
		else if(S_ISSOCK(buf.st_mode))
			ptr = "socket";
		else
			ptr = "unknown mode";

		if(buf.st_mode & S_ISUID)
			printf(" set-user-id ");
		if(buf.st_mode & S_ISGID)
			printf(" set-group-id ");
		printf("%s\n",ptr);
	}
	exit(0);
}
