#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<sys/msg.h>

#define SHARED_SIZE 500

struct msgbuff
	{
	long mtype;
	int message;
	}s;

void attach(key_t key,int shm_id,int *shared_memory)
	{
		if((shm_id=shmget(key,sizeof(char)*SHARED_SIZE,IPC_CREAT|0666))<0)
			perror("attach:get");
		if((shared_memory=shmat(shm_id,NULL,0))==(int *)-1)
			perror("attach:shmat");
		printf("\n Memory attached at address %d",&shared_memory);
		//send(shm_id,shared_memory);
	}


void detach(int *shared_memory)
	{
		if(shmdt(shared_memory))
			printf("\n Memory detached");
	}

void create_process(pid_t child_p1,pid_t child_p2,int stored_value)
{

	int a=10;
	int b=20;
	printf("\n---------------------------------------------------");	
	printf("\n Process id for parent process is %d",(int)getppid());
	printf("\n Process id for child process= %d",(int)child_p1);
	printf("\n Process id for another process= %d",(int)child_p2);
	printf("\n--------------------------------------------------");
	child_p1=fork();
	child_p2=fork();	
	if(!child_p1)
		{
		stored_value=stored_value+a; //sum of value+10;
		printf("\n Stored value modified %d by process %d",stored_value,(int)getpid());
		}
	if(!child_p2)
		{
		stored_value=stored_value+b; //sum of value+20;
		printf("\n Stored value modified %d by process %d",stored_value,(int)getpid());
		}
	

}

int send(int shm_id,int *shared_memory)
	{
		
		int *message;
		message=shared_memory;
		message=malloc(sizeof(int)*2);
		printf("\n Allocation successfull");
		printf("\n Enter the value...");
		scanf("%d",&message);
		printf("\n Value stored");		
		//
		/*(while(*message!='0')
		{
		sleep(1);
		}*/
		printf("\n Message in shared memory");		
		return(message);
		
	}

void msg_send(key_t key,int stored_value)
	{
	s.mtype=1;
	int msg_id;
	if((msg_id=msgget(key,IPC_CREAT|0666))==-1)
		perror("Msgget");
	s.message=stored_value;
	int result=msgsnd(msg_id,(void*)&s,sizeof(s.message),IPC_NOWAIT);
	if(result==0)
		printf("\n Message sent!!");
	else
		printf("\n Message:error");
	}


int main()
{
	int shm_id;
	int *shared_memory;
	key_t key;
	key=ftok("/home/ankit/Desktop/LKA/quadcomm.c",1);
	if(key==-1)
		perror("\n Key not generated");
	printf("\n Generated key %d",key);
	printf("\n Attaching memory space");
	attach(key,shm_id,shared_memory);	
	printf("\n Memory space attached...");
	static int *stored_value;
	stored_value=send(shm_id,shared_memory);
	printf("\n Stored value %d",stored_value);
	printf("\n Calling create process...");
	pid_t child_p1,child_p2;
	create_process(child_p1,child_p2,stored_value);
	msg_send(key,stored_value);	
	detach(shared_memory);
	printf("\n Memory space detached");
	printf("\n Stored value %d",stored_value);
	exit(0);
}
