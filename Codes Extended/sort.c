
#include<sys/types.h>
#include<sys/ipc.h>
#include<stdio.h>
#include<stdlib.h>
#define SIZE 300

void attach(key_t key,int shm_id,int *shared_mem)
	{
	if((shm_id=shmget(key,sizeof(int)*SIZE,0666))< 0)
		perror("attach:shmget");
	if((shared_mem =(int*)shmat(shm_id,NULL,0)) == -1)
		perror ("attach:shmat");
	printf("\n Memory space attached %d",shared_mem);
	}

void detach (int *shared_mem)
	{
		if(shmdt(shared_mem))
		{
		printf ("\n Memory detached");
		}
	}

void sort(int size,int array[])
{
int i;
if(size==0)
	exit(0);
else
	{
	for (i=0;i<size;i++)
	{
	printf("\n Enter the %d element" ,i);
	scanf("%d",&array[i] );
	}
	int i,j;
	for (i=0;i<size;i++)
		{
		for (j=i+1;j<size;j++)
		{
			if(array[i]>array[j])
			{			
			int temp=array[i];
			array[i]=array[j];
			array[j]=temp;
			}
		}
	}
	}
}

void display(int size,int array[])
{
	int i;
	for(i=0;i<size;i++)
	{
		printf("\n");
		printf( "%d",array[i]);
	}
}

int main()
{
int shm_id;	
int key=1234;
int *shared_mem;
int size;
printf("\n Enter the size of the array:");
scanf("%d",&size);
//int array[size];
printf("\n Attaching memory");
attach(shm_id,key,shared_mem);
printf("\n The size of the array %d",size);
sort (size,shared_mem);
printf("\n Displaying the sorted array:");
display(size,shared_mem);
detach(shared_mem);
printf("\n end main");
return 0;
}

