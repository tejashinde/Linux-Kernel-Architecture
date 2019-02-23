#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/stat.h>
#include<unistd.h>
#define SIZE 500

void attach(key_t key,int shm_id,char *shared_mem)
	{
	if((shm_id=shmget(key,sizeof(char)*SIZE,0666)) <0)
		perror("attach:shmget");
	if((shared_mem=shmat(shm_id,NULL,0))==(char *)-1)
		perror("attach:shmat");
	printf("\n Memory space attached at %d",&shared_mem);
	printf("\n Reading message...");
	for(char *r=shared_mem;*r!='\0';r++)
		{putchar(*r);		
		}
		//printf("Message %s",buffer.message);
	putchar('\n');

	*shared_mem='*';
	
	}

int main()
	{
	int shm_id;	
	key_t key;
	char *shared_mem;
	key=ftok("/home/ankit/Desktop/LKA/ipc_server.c",1);
	if(key==-1)
		perror("\n Key not generated");
	printf("\n Process id=%d",(int)getpid());
	printf("\n Parent process id=%d",(int)getppid());	
	printf("\n Generated key %d",key);
	printf("\n Attaching memory space");
	attach(key,shm_id,shared_mem);
	return 0;
	}

