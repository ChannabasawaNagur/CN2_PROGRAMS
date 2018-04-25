#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
#include<sys/stat.h>

#define MAX 10000

typedef struct msg{
  long mtype;
  char mtext[MAX];
}msg_buf;

int main()
{
  int msgqid1,msgqid2;
  int buf_length;
  key_t key1,key2;
  key1 = 1234;
  key2 = 5678;
  msg_buf buf;
  int msgflag=  0666;

  if((msgqid1=msgget(key1,msgflag))<0)
  {
    printf("queue open failed...\n" );
    exit(0);
  }
  else
  {
    printf("Client queue opened successfully....\n");
  }

  if((msgqid2=msgget(key2,msgflag))<0)
  {
    printf("queue open failed...\n");
    exit(0);
  }
  else
  {
    printf("Queue opened successfully....\n");
  }
  buf.mtype=1;
  printf("enter the file to be received...");
  scanf("%s",buf.mtext);
  buf_length=strlen(buf.mtext)+1;
  if(msgsnd(msgqid1,&buf,buf_length,IPC_NOWAIT)<0)
  {
    printf("msg not sent...\n");
    exit(0);
  }
  else
  {
    printf("msg sent successfully....waiting for reply...\n");

  }

  if(msgrcv(msgqid2,&buf,sizeof(buf),2,0)<0)
  {
    printf("msg receive failed...\n");
    return 0;
  }
  else
  {
    fputs(buf.mtext,stdout);
    printf("\n");
    return 0;
  }

  return 0;

}
