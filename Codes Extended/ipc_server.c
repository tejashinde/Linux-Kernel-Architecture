#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>

#define SIZE 500 
//struct shmid_ds sharedbuff;


//struct msgbuff buffer;	
void send(int shm_id,char *shared_memory)
	{
		//int rc=shmctl(shm_id,IPC_STAT,&sharedbuff);
		//if(rc==-1)
			//perror("send:shmctl");
		char *message;
		message=shared_memory;
		for(char *c='a';c<='k';c++)
			*message++=(int)c;		
		//scanf("%s",&shared_memory);		
		//
		while(*shared_memory!='*')
		{
		sleep(1);
		}
		printf("\n Message in shared memory");		
		//shared_memory=buffer.message;
		
		
	}
void attach(key_t key,int shm_id,char *shared_memory)
	{
		if((shm_id=shmget(key,sizeof(char)*SIZE,IPC_CREAT|0666))<0)
			perror("attach:get");
		if((shared_memory=shmat(shm_id,NULL,0))==(char *)-1)
			perror("attach:shmat");
		printf("\n Memory attached at address %d",&shared_memory);
		send(shm_id,shared_memory);
	}

void detach(char *shared_memory)
	{
			if(shmdt(shared_memory))
				printf("\n Memory detached");
	}



int main()
	{
	int shm_id;
	char *shared_memory;
	key_t key;
	key=ftok("/home/ankit/Desktop/LKA/ipc_server.c",1);
	if(key==-1)
		perror("\n Key not generated");
	printf("\n Generated key %d",key);
	printf("\n Attaching memory space");
	attach(key,shm_id,shared_memory);
	//detach(shared_memory);
	int return_value;
	return_value=system("ls -lh");
	return_value;
	}

