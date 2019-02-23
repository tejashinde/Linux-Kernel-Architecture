#include<sys/msg.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<stdio.h>
#include<pthread.h>
#include<sys/sem.h>
#include<semaphore.h>

struct msgbuff
	{
	long msgtype; //type of message
	char msg[100];
	}sender;
struct rmsgbuff
	{
	long msgtype;
	char msg[100];
	}reciever;

	struct msgqid_ds *rbuff;

void *recieve(key_t key,int msg_id)
	{
	if((msg_id=msgget(key,IPC_CREAT|0666))==-1)
		{
		perror("\n Unable to generate msg_id");
		exit(0);
		}
	int stats=msgctl(msg_id,IPC_STAT,&rbuff);
	if(stats==-1)
		{
		printf("\n Message control failed");
		}
	//int msg=rbuff.msg_qnum;
	printf("\n Retrieving message.");
	if((msgrcv(msg_id,(void*)&reciever,sizeof(sender.msg),1,IPC_NOWAIT)) < 0)
	{
		perror("\n Unable to retrieve message");
	}
	printf("\n %s",reciever.msg);
	}


void *send(key_t key,int msg_id)
	{
	if((msg_id=msgget(key,IPC_CREAT|0666))==-1)
		{
		perror("\n Unable to generate msg_id");
		exit(0);
		}
	printf("\n Message id generated succesfully");
	printf("\n Enter the message to send.");
	scanf("%s",&sender.msg);
	if((msgsnd(msg_id,(void*)&sender,sizeof(sender.msg),IPC_NOWAIT)) < 0)
	{
		perror("\n Unable to send message");
		exit(0);
	}
	printf("\n Message sent successfully");
	}


int main()
	{
	pthread_t t1,t2;
	sem_t mysem;
	sem_init(&mysem,0,1);
	sender.msgtype=1;	
	reciever.msgtype=1;	
	int msg_id;
	key_t key;
	key=12345;
	pthread_create(&t1,NULL,send,NULL);
	//send(key,msg_id);
	printf("\n Setting up semaphore....");
	sem_wait(&mysem);
	printf("\n Waiting for reciver...");
	pthread_create(&t2,NULL,recieve,NULL);
	//sleep(4);
	sem_post(&mysem);
	//recieve(key,msg_id);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	sem_destroy(&mysem);
	printf("\n Semaphore destroyed");
	return(0);
	}
	
	
