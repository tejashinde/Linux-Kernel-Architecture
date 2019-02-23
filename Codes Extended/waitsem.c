#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/sem.h>

#define SHMSZ 1024
key_t key=1234;

union semun
	{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *_buf;
	}sem_val;

//Obtain a binary semaphore's address

	int binary_semaphore_allocation(key_t key,int sem_flags)
	{
		return semget(key,1,sem_flags);
	}
	
//Deallocate a binary semaphore 

int binary_semaphore_deallocation(int semid)
	{
	union semun ignored_arg;
	return semctl(semid,1,IPC_RMID,ignored_arg);
	}
//Wait 

int binary_semaphore_wait(int semid)
{
	struct sembuf operations[1];
	// First and only semaphore
	operations[0].sem_num=0;
	// Decrement by 1. 
	operations[0].sem_op=-1;
	// pemit undo
	operations[0].sem_flg=SEM_UNDO;
	return semop(semid,operations,1);
}

int binary_semaphore_post(int semid)
{
	struct sembuf operations[1];
	//Use the first and only semaphore
	operations[0].sem_num=0;
	//Increment by 1
	operations[0].sem_op=1;
	//Permit undo			
	operations[0].sem_flg=SEM_UNDO;
	return semop(semid,operations,1);
}

void recieve(int segment_id)
{
	//key_t key=1234;
	char*message,*s;
	
	if((segment_id=shmget (key,sizeof(char)*SHMSZ,0666))<0)
	{
		perror("Recieve:receive");	
	}	
	if((message=shmat (segment_id,NULL,0))==(char *) -1){
		perror("Recieve: Shmat");
	}
	for(s=message;*s!=NULL;s++)
	{
		printf("%s",&s);
	}
	*message='*';
}

void send()
{
	int sem_id; 		//id for semaphore
	int segment_id;
	key_t key=1234;
	char *shared_memory;
	struct shmid_ds shmbuffer;
	//Allocate binary semaphore	
	sem_id=binary_semaphore_allocation(key,IPC_CREAT|0666);
	if(sem_id==-1)
		perror("send:Semget");
	//Initializing the value of semaphore..
	sem_val.val=1;
	int status=semctl(sem_id,0,SETVAL,sem_val);
	if(status==-1)
		perror("send:Semctl");	
	//Allocate a shared memory segment
	if((segment_id=shmget(key,sizeof(char)*SHMSZ,IPC_CREAT|0666)) < 0);
	//Attach the memory segment
	printf("\n Segment_id:%d",segment_id);
	if((shared_memory=shmat(segment_id,NULL,0))==(char *)-1)
		perror("\n Cannot attach to specified space");
		
	printf("\n Shared memory attached address %d",shared_memory);
	int stat=shmctl(segment_id,IPC_STAT,&shmbuffer);
	if(stat==-1)
		perror("Send:shmctl");
	int size=shmbuffer.shm_segsz;
	printf("\n Segment size- %d",size);
	//Write 
	sprintf(shared_memory,"Hello!");
	printf("Message successfull");
	printf("\n Implementing semaphore...");
	printf("\n Implementing read at segment id %d",segment_id);
	int wait=binary_semaphore_wait(sem_id);
	printf("\n Semaphore status :Wait...");		
	recieve(segment_id);
	while(*shared_memory!='*')
		{
		sleep(1);
		}
	printf("\n Read completed..");
	int post=binary_semaphore_post(segment_id);
	printf("\n Semaphore status: Post");
	printf("\n Deallocating semaphore for id %d",sem_id);
	int detach=binary_semaphore_deallocation(sem_id);
	if(detach==-1)
		perror("Deallocation failed..");
	else
		perror("Deallocation success.");

}


int main()
{				
	send();		
}





