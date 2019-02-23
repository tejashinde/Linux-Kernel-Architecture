#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/types.h>
#include<stdio.h>

//Define udd for semaphore

union semun
	{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct semifno *_buf;
	}s;

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
int main()
{
	s.val=1;
	key_t key=1234;
	int allocation=binary_semaphore_allocation(key,IPC_CREAT);
	printf("\n Semaphore allocated successfully at key: %d",key);
	printf("\n %d",allocation);
	printf("\n Deallocating semaphore...");
	int dealloc=binary_semaphore_deallocation(allocation);
	printf("\n Deallocation successfull");
	printf("\n %d",dealloc);
	return 0;	
}

