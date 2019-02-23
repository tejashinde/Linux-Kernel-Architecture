#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>

struct msgbuff
	{
	long mtype;
	int message;
	}r;
struct msqid_ds buff;
void recieve(key_t key)
	{
	int msg_id,result;
	if((msg_id=msgget(key,IPC_CREAT|0666))==-1)
	{
		perror("Msgget");
		exit(-1);
	}
	printf("\n Fetching message");
	int c;
	c=msgctl(msg_id,IPC_STAT,&buff);
	result=msgrcv(msg_id,(void*)&r,sizeof(r.message),0,0);
	if(result==0)
		{
		printf("\n %d",r.message);
		}
	else
		{
		printf("\n Message recieved failed");
		}
	}

int main()
	{
	key_t key;
	key=ftok("/home/ankit/Desktop/LKA/quadcomm.c",1);
	if(key==-1)
		perror("Key cannot be generated");
	printf("\n Generate key= %d",key);
	r.mtype=1;
	printf("\n Retreiving message");
	recieve(key);
	exit(0);
	}
