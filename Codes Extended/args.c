#include<stdio.h>

int main(int argc,char * argv[])
{
	printf("\n First argument is %s",argv[0]);
	printf("\n Length of the arguments are %d",argc);
	printf("\n Printing the arguments..");
	int i;
	for(i=0;i<argc;i++)
	{
		printf("%s",&argv[i]);
	}
return 0;
}
