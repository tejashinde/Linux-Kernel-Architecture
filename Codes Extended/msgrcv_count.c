#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>

#define MSG_BUFF 2
typedef struct msgbuff
{
	long mtype;
	int message[MSG_BUFF];
} message_buff;

int main()
{
int running=1;
int mqid;
int rc;
key_t key;
struct msqid_ds buff;
message_buff rbuf;
key=1234;
int num_messages;
mqid=msgget(key,IPC_CREAT);
if(mqid==-1)
{
	perror("msgget failed");
	exit(1);
}
rc=msgctl(mqid,IPC_STAT,&buff);
num_messages=buff.msg_qnum;

if(num_messages==0)
{
	perror("\n Queue is empty");
	exit(1);
}

if(msgrcv(mqid,&rbuf,MSG_BUFF,1,0)<0)
{
	perror("Msgrcv");
	exit(1);
}

printf("\n Recieved result from message_id %d",mqid);
printf("\n %d",rbuf.message[0]);
int recieved=rbuf.message[0];
int value1;
printf("\n Enter a number to multiply the result");
scanf("%d",&value1);
printf("\n Computing value...");
int result;
result=recieved*value1;
printf("\n The final result is %d",result);
exit(0);
}
