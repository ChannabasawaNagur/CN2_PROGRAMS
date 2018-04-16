//Server using Message Queue
#include <sys/types.h>
#include<string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include<fcntl.h>
#define MSGSZ     10000
/* Declare the message structure.*/
typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;
int main()
{
    int msqid1,msqid2,f1,filesize,n;
    key_t key1,key2;
    message_buf  buf;
    size_t buf_length;
    /*Key1 for MQ1 & Key2 for MQ2*/
    key1 = 1234;
    key2 = 5678;
    if ((msqid1 = msgget(key1, 0666)) < 0) {
         printf("SERVER : Can't open input message queue \n");
        return 0;
    }
    else
      printf("SERVER : Input message queue opened successfully\nSERVER : Waiting for client request..\n");  
    /*Receive an answer of message type 1.*/
    if (msgrcv(msqid1, &buf, MSGSZ, 1, 0) < 0) {
        printf("SERVER : Can't receive the message..\n");
        return 0;
    }
   if ((msqid2= msgget(key2, 0666 )) < 0) {
        printf("SERVER : Can't open output message queue \n");
        return 0;
    }
    else 
     printf("SERVER : Output message queue opened succesfully\n");
     buf.mtype = 2;
      if((f1=open(buf.mtext,O_RDONLY))!=-1)
	{
        printf("\nSERVER : %s is found \nTransfering the contents.. \n",buf.mtext);
		filesize=lseek(f1,0,2);
		printf("\nSERVER : File size is %d\n",filesize);
		lseek(f1,0,0);//rewind file pointer to beginning
		n=read(f1,buf.mtext,filesize);
               buf_length = strlen(buf.mtext) + 1 ;
               if (msgsnd(msqid2, &buf, buf_length, IPC_NOWAIT) < 0) {
                printf("SERVER : Error on message sending..\n");
                 return 0;
                }
              else 
               printf("SERVER : File contents transfered successfully..\n\n");
          }
        else
       {
	       printf("SERVER : File %s not found\n",buf.mtext);
               strcpy(buf.mtext, "File Not Found");
               buf_length = strlen(buf.mtext) + 1 ;
               if (msgsnd(msqid2, &buf, buf_length, IPC_NOWAIT) < 0) {
                  
               printf("SERVER : Error on message sending.. \n");
                 return 0;
                }
              else 
               printf("SERVER : Reply sent to client successfully..\n\n");
       }
       return 0;
}

