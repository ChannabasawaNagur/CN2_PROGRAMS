#include<stdio.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

#define MAX 10000

typedef struct msgbuf{
  long int mtype;
  char mtext[MAX];
}msg_buf;

int main()
{
  int msgqid1,msgqid2,f,filesize,n;
  key_t key1,key2;
  key1 = 1234;
  key2=5678;
  msg_buf buf;
  size_t buf_length;
  if((msgqid1=msgget(key1,0666 | IPC_CREAT))<0){
    printf("%d\n",msgqid1);
    printf("%s\n",strerror(errno));
    printf("q1 cant be opened...\n");
    return 0;
  }
  else
    printf("i/p msg queue opened...\n");
  if((msgqid2=msgget(key2,0666 | IPC_CREAT))<0){
    printf("cant open o/p msg queue...\n");
    return 0;
  }
  else
    printf("o/p msg queue opened successfully...\n");
  if(msgrcv(msgqid1,&buf,sizeof(buf) ,1,0)< 0 )
  {
    printf("cant receive the msg....\n");
    return 0;
  }
  else
  {
    printf("msg received succesfully...%s\n",buf.mtext);
  }
  buf.mtype=2;
  if((f=open(buf.mtext,O_RDONLY))!=-1)
  {
    printf("Transfering files...\n");
    filesize=lseek(f,0,2);
    lseek(f,0,0);
    n=read(f,buf.mtext,filesize);
    buf_length = strlen(buf.mtext)+1;
    int retval;
    if((msgsnd(msgqid2,&buf,buf_length,IPC_NOWAIT))<0)
    {
      printf("retval:%d\n",retval );
      printf("errno:%d",errno);
      printf("error in sending msg...\n");
      return 0;
    }
    else
      printf("file contents transfered...\n");
  }
  else
  {
    printf("file not found...\n");
    strcpy(buf.mtext,"file not found");
    buf_length=strlen(buf.mtext)+1;
    if(msgsnd(msgqid2,&buf,buf_length,IPC_NOWAIT)<0){
      printf("server msg not sent...\n");
      return 0;
    }
    else
      printf("msg sent...\n");
  }
  return 0;


}
