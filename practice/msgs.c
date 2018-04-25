#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<fcntl.h>
#include<string.h>
#include<sys/ipc.h>
#define MSGSZ 10000

typedef struct {
  long msgtype;
  char msgtxt[MSGSZ];
}msgbuf;

int main()
{
  int msgqid1,msgqid2,f1,filesize,n;
  key_t key1,key2;
  size_t buf_length;
  msgbuf buf;
  key1=1234;
  key2=5678;
  if((msgqid1=msgget(key1,0666))<0)
  {
    printf("SERVER: ERROR in opening msg queue1\n");
    return 0;
  }
  else
    printf("SERVER: msgqueue1 opened successfully\n");

  if((msgrcv(msgqid1,&buf,MSGSZ,1,0))<0)
  {
    printf("SERVER: cant receive the msg\n");
    return 0;
  }
  else
    printf("SERVER: msg received successfully\n");
  if((msgqid2=msgget(key2,0666))<0)
  {
    printf("SERVER: cant open msgqueue2 \n");
    return 0;
  }
  else
    printf("SERVER: msgqid2 opened successfully\n");

  buf.msgtype=2;
  if((f1=open(buf.msgtxt,O_RDONLY))!=-1)
  {
    printf("SERVER: %s if found, sending files...\n",buf.msgtxt);
    filesize=lseek(f1,0,2);
    printf("file size is %d:\n",filesize);
    lseek(f1,0,0);
    n=read(f1,buf.msgtxt,filesize);
    buf_length=strlen(buf.msgtxt)+1;
    if((msgsnd(msgqid2,&buf,buf_length,IPC_NOWAIT))<0)
    {
      printf("SERVER: msg cannot be sent:\n");
      return 0;
    }
    else
      printf("SERVER: msg sent succesfully\n");
  }
  else
  {
    printf("SERVER: file %s not found:\n",buf.msgtxt);
    strcpy(buf.msgtxt,"file not found...");
    if(msgsnd(msgqid2,&buf,strlen(buf.msgtxt)+1,IPC_NOWAIT))
    {
      printf("SERVER: msg sent succesfully\n");
      return 0;
    }
    else
      printf("SERVER: msg sent succesfully\n");
  }
  return 0;

}
