//To create a program that demonstrates IPC 

#include<stdio.h>
//#include<conio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<stdlib.h>

#define MSGBUFF 2
//#define KEYSIZE 10

typedef struct msgbuf
{
long m_type;
int message[MSGBUFF];
}message_buf;

void main()
{
int mq_id;
int msgflg=IPC_CREAT;
key_t key;
message_buf sbuf;
size_t buff_length;
key=1234;
if((mq_id=msgget(key,msgflg))<0)
	{
	perror("Message get");
	exit(1);
	}
else
	(void) fprintf(stderr,"Msgget: Message get succeded: mq_id=%d\n",mq_id);
	
sbuf.m_type=1;
int value1,value2,result;
printf("\n Enter the value for operand 1:");
scanf("%d",&value1);
printf("\n Enter the value for operand 2:");
scanf("%d",&value2);
printf("\n Calculating the result");
result=value1+value2;
sbuf.message[1]=result;
printf("\n Result %d",result);
//strcpy(sbuf.message,"Hello!!!!!");
buff_length=sizeof(int)*MSGBUFF;

if(msgsnd(mq_id,&sbuf,buff_length,IPC_NOWAIT)<0)
{
printf("\n%d, \n%ld, \n%s, \n%d\n",mq_id,sbuf.m_type,sbuf.message,buff_length);
perror("msgsnd");
exit(1);
}

}

