#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>

#define SEM_ID 100
#define SIZE 500
struct shmid_ds shared_ds;
struct shared_message
	{
	char message[SIZE];
	};
struct shared_message msg;	

union semun
	{
	int val;
	struct semid_ds *buff;
	ushort *array;
	}sem_val;

void sem_wait(int sem_set_id)
	{
	struct sembuf sem_op;
	//Locking on semaphore,for negative value
	sem_op.sem_num=0;
	sem_op.sem_op=-1;
	sem_op.sem_flg=0;
	semop(sem_set_id,&sem_op,1);
	}

void sem_post(int sem_set_id)
	{
	struct sembuf sem_op;
	//Unlocking semaphorem,on positive value
	sem_op.sem_num=0;
	sem_op.sem_op=1;
	sem_op.sem_flg=0;
	semop(sem_set_id,&sem_op,1);
	}
void send(int sem_set_id)
	{
	sem_wait(sem_set_id);
	printf("\n Enter the message for shared address");
	scanf("%s",&msg.message);
	sem_post(sem_set_id);
	}
void attach(key_t key,int shm_id,char *shared_mem,int sem_set_id)
{
	
	shm_id=shmget(key,sizeof(msg),IPC_CREAT|0640);
	if(shm_id==-1)
		perror("Attach:shmget");
	shared_mem=(char*)shmat(shm_id,NULL,0);
	printf("\n Segment memory at %d",shared_mem);
	send(sem_set_id);
	if((void*)shared_mem==-1)
		perror("attach:");
	int ctl=shmctl(shm_id,IPC_STAT,&shared_ds);
	if(ctl==-1)
		perror("\n shmctl:");
	int size=shared_ds.shm_segsz;
	printf("\n Message for shared memory %c",msg.message);
	printf("\n Segment size %d",size);
	
	
}

void detach(int shm_id,char *shared_mem)
{
	//shmdt(shared_mem);
	if(shmdt(shared_mem)==-1)
		perror("detach:shmdat");
	if(shmctl(shm_id,IPC_RMID,NULL)==-1)
	{
		perror("detach:");
		exit(1);
	}
	else
	{
	printf("\n Memory detached at address %d",shared_mem);
	}	

}
main()
{
	key_t key;
	key=ftok(".",2);
	printf("Generated key %d",key);
	int shm_id;
	int sem_set_id;
	char *shared_mem;
	sem_set_id=semget(SEM_ID,1,IPC_CREAT|0600);
	if(sem_set_id==-1){
		perror("Main:semctl");
		exit(1);}	
	//Initialize binary semaphore to 1
	sem_val.val=1;
	int rc;
	rc=semctl(sem_set_id,0,SETVAL,sem_val);
	if(rc==-1)
	{
		perror("Main:semctl");
		exit(1);
	}
	attach(key,shm_id,shared_mem,sem_set_id);
	detach(shm_id,shared_mem);
	exit(0);
}


