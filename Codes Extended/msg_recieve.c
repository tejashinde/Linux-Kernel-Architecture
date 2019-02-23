#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<string.h>

#define MSG_BUFF 100

typedef struct msg_rec
{
	char message[MSG_BUFF];

}message_buff;

void main()
{
int mq_id; //id of message queue
key_t key; //naming the memory area by using the key
message_buff rbuff;
key=1234;
if((mq_id=msgget(key,IPC_CREAT))<0)
{
perror("Msgget");
exit(1);
}

if(msgrcv(mq_id,&rbuff,MSG_BUFF,1,0)<0)
{
perror("Msgrcv");
exit(1);
}
printf("\n Message recieved from mq_id :%d",mq_id);
printf("\n %s\n",rbuff.message);
exit(0);
}
