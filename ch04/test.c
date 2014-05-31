#include <stdio.h>

//typedef int Myfunc(int,int);
//static Myfunc myfunc;
static int myftw(int, Myfunc *);

int main(void)
{
	int i,result;
	i = myfunc(1,2);
	result = myftw(i,myfunc);
	printf("%d,%d\n",i,result);
	return 0;
}

static int myfunc(int i,int j)
{
	return i + j;

}

static int myftw(int a, Myfunc *myfunc)
{
	//TODO
	return a+myfunc(100,100);
	
}
