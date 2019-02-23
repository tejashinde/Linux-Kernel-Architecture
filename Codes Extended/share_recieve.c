#include<stdio.h>
#include<sys/shm.h>
#include<sys/stat.h>


int main()
{
	int segment_id;
	key_t key=1234;
	char* shared_memory;
	struct shmid_ds shmbuffer;
	int segment_size;
	const int shared_segment_size=0x1000;
	//Allocate a shared memory segment
	segment_id=shmget(key,shared_segment_size,IPC_CREAT|IPC_EXCL|S_IRUSR|S_IWUSR);
	//Attach the memory segment
	shared_memory=(char*)shmat(segment_id,(void*)0x1000,0);
	printf("\n Shared memory attached address %d",shared_memory);
	shmctl(segment_id,IPC_STAT,&shmbuffer);
	segment_size=shmbuffer.shm_segsz;
	printf("\n Segment size- %d",segment_size);



//Re-attach
	shared_memory=(char*)shmat(segment_id,(void*)0x5000,0);
	printf("Shared memory reattached at address..%d",shared_memory);
	printf("\n %s",shared_memory);
	//Detach
	shmdt(shared_memory);

	//Deallocate
	shmctl(segment_id,IPC_RMID,0);
	return 0;
}
