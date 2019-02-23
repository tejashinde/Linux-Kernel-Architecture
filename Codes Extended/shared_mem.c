#include<stdio.h>
#include<sys/shm.h>
#include<sys/stat.h>
#define SIZE 500
int main()
{
	int segment_id;
	key_t key=12;
	char* shared_memory;
	struct shmid_ds shmbuffer;
	int segment_size;
	//Allocate a shared memory segment
	segment_id=shmget(key,SIZE,IPC_CREAT|IPC_EXCL|S_IRUSR|S_IWUSR|0777);
	if(segment_id==-1)
		perror("Segment id");
	//Attach the memory segment
	shared_memory=(char*)shmat(segment_id,0x2222,0);
	printf("\n Shared memory attached address %d",shared_memory);
	shmctl(segment_id,IPC_STAT,&shmbuffer);
	segment_size=shmbuffer.shm_segsz;
	printf("\n Segment size- %d",segment_size);
	//Write 
	sprintf(shared_memory,"Hello!");
	//Detaching segment
	shmdt(shared_memory);

	//Re-attach
	shared_memory=(char*)shmat(segment_id,(void*)0x19000,0);
	printf("\n Shared memory reattached at address..%d",shared_memory);
	printf("\n %s",shared_memory);
	//Detach
	shmdt(shared_memory);
	
	
	//Deallocate
	shmctl(segment_id,IPC_RMID,0);
	return 0;
}
