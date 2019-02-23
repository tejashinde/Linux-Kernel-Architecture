/*To write a program that implements two way interprocess communication
Name :Ankit Patel
Date :8-1-19 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<string.h>
//#include<mqueue.h>
//#include<pthread.h>

//defining buufer size
#define MSGSIZE 500


//Buffer for sending
typedef struct msgbuff
	{
	long message_type;
	char message[MSGSIZE];
	};

struct msgbuff sbuff;

//Buffer for recieving
typedef struct msgrbuff
	{
	long message_type;
	char message[MSGSIZE];
	};
struct msqid_ds buff;
struct msgbuff rbuff;


void send(key_t key,int msgflag,int message_qid,size_t buffer_len)
{
	if ((message_qid=msgget(key,msgflag)) <0)
		perror("Send:msget");
	sbuff.message_type=1;
	printf("\n Enter the message to send...");
	scanf("%s",sbuff.message);
	//getchar();
	buffer_len=strlen(sbuff.message)+1;
	if (msgsnd(message_qid,&sbuff,buffer_len,IPC_NOWAIT) <0)
	{
		printf("\n Message not send");
		printf("\n %d,%d,%s,%d\n",message_qid,sbuff.message_type,sbuff.message,buffer_len);
	}
	else
	{
		pid_t pid;
		if(pid==fork())
			printf("\n Process created..");
		if(pid==0)
			{	
		int control=msgctl(message_qid,IPC_STAT,&buff);
		if(control==-1)
			perror("MsgCTL:send");
		int id=buff.msg_lspid;
		printf("\n Process ID: %d",id);
		printf("\n Message sent successfully!");
		printf("\n Message details:");
		printf("\n Message queue id status %d",message_qid);
		printf("\n Message :%s",sbuff.message);
			sleep(10000);
			}
		else
			printf("\n Sleep erorr");		
		
	}
}

void recieve(key_t key)
{
	int message_id;

	if (message_id=msgget(key,0666|IPC_CREAT))
		perror("Recieve:msgrcv");
	if(msgctl (message_id,IPC_STAT,&buff)==-1)
		{
		perror("Message control failed");
		exit(1);
		}
	int message_cnt=buff.msg_qnum;
	int id=buff.msg_lspid;
	if(message_cnt==0)
		printf("\n No more messages to the display. \n Empty Queue");
	else
	{
	if (msgrcv(message_id,&rbuff,MSGSIZE,1,0) <0)
		perror("\n Error..");
	printf("\n Message id set to calling process %d",id);
	printf("\n Message recieved...");
	printf("\n Key:%d",key);
	printf("\n Message sent was:%s",rbuff.message);
	printf("\n Queue Message count=%d",message_cnt);
	}
}

int main()
{
	
	
	int message_qid;
	int msgflag=IPC_CREAT|0666;
	key_t key;
	size_t buffer_len;
	
	
	//for(char i='a';i<='c';i++){
		key=ftok("/home/ankit/Desktop/LKA/ipc_comm.c",1);
	//}
	while(1)
	{
		printf("\n**********************");
		printf("\n IPC communication");
		printf("\n----------------------");
		printf("\n 1. View Key");
		printf("\n 2. Send");
		printf("\n 3. Recieve");
		printf("\n 4. Exit"); 
		printf("\n----------------------");
		printf("\n**********************");
		printf("\n Enter your choice");
		int ch;
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: printf("\n Generated key= %d",key);
				break;
			
			case 2:send(key,msgflag,message_qid,buffer_len);	
				break;	
			
			case 3:recieve(key);	break;
			
			case 4:exit(0);
			
			default:printf("\n Enter a valid choice..");
		}				
	}
	return 0;
}


	
