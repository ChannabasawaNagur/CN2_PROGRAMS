#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/msg.h>
#include<string.h>
#define MSGSZ 10000

typedef struct {
	long msgtype;
	char msgtxt[MSGSZ];
}msgbuf;

int main()
{
	int msgqid1,msgqid2;
	key_t key1,key2;
	int msgflag = IPC_CREAT | 0666 ;
	int buf_length;
	key1=1234;
	key2=5678;
	msgbuf buf;
	if((msgqid1=msgget(key1,msgflag))<0)
	{
			printf("CLIENT: cant open msgqueue1\n");
			return 0;
	}
	else
	{
		printf("CLIENT : MSGqueue1 opened succesfully\n");
	}
	if((msgqid2=msgget(key2,msgflag))<0)
	{
		printf("CLIENT : cant open msgqueue2\n");
		return 0;
	}
	else
	printf("CLIENT: msgqueue2 opened succesfully\n");
	buf.msgtype=1;
	printf("enter the filename to be fetched\n");
	scanf("%s",buf.msgtxt);
	buf_length = strlen(buf.msgtxt)+1;
	printf("waiting for reply\n");
	if(msgsnd(msgqid1,&buf,buf_length,IPC_NOWAIT)<0){
		printf("CLIENT: error on sending filename\n");
		return 0;
	}
	else
		printf("CLIENT: filename sent succesfully...waiting for reply...");
		if((msgrcv(msgqid2,&buf,MSGSZ,2,0))<0)
		{
			printf("CLIENT : error while receiving the file\n");
			return 0;
		}
		else
		{
			printf("CLIENT: reply from server\n");
			fputs(buf.msgtxt,stdout);
			printf("\n\n");
		}
		return 0;

}
