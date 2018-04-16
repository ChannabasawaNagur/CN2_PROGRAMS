//Client using Message Queue
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#define MSGSZ    10000
// Declare the message structure.
typedef struct msgbuf {
         long    mtype;
         char    mtext[MSGSZ];
         } message_buf;
int main()
{
    int msqid1,msqid2;
    int msgflg = IPC_CREAT | 0666;
    key_t key1,key2;
    message_buf buf;
    size_t buf_length;
  /*Key1 for MQ1 & Key2 for MQ2*/
    key1 = 1234;
    key2=5678;
    if ((msqid1 = msgget(key1, msgflg )) < 0) {
        printf("CLIENT: Can't open output message queue \n");
        return 0;
    }
    else 
     printf("CLIENT : Output message queue opened successfully\n");
    if ((msqid2= msgget(key2, msgflg )) < 0) {
        printf("CLIENT : Can't open input message queue \n");
        return 0;
    }
    else 
     printf("CLIENT : Input message queue opened successfully\n");
         /*send message type 1*/
         buf.mtype = 1;
    printf("\nEnter the filename : ");
    scanf("%s",buf.mtext);
    buf_length = strlen(buf.mtext) + 1 ;
    /* Send  the filename*/
    if (msgsnd(msqid1, &buf, buf_length, IPC_NOWAIT) < 0) {
       
        printf("CLIENT : Error on sending filename\n");
        return 0;
    }
   else 
      printf("CLIENT :Filename sent to the server.. waiting for reply..\n");
       if (msgrcv(msqid2, &buf, MSGSZ, 2, 0) < 0) {
        printf("CLIENT : Error on receiving the reply..\n");
        return 0;
    }
  else
  {
    printf("CLIENT : Reply from server:\n");
    fputs(buf.mtext,stdout);
    printf("\n\n");
   } 
     return 0;
}

