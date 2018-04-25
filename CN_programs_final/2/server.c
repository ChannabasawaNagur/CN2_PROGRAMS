#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#define MAX 1000
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define PERMS 0666
char fname[1000];
char buffer[1000];

int main()
{
  int readfd,writefd,n,fd;
  printf("waiting for connection....\n" );
  if((mkfifo(FIFO1,PERMS))<0)
  {
    printf("cannot make file...\n");
    exit(0);
  }
  if((mkfifo(FIFO2,PERMS))<0)
  {
    printf("cannot make file 2....\n" );
    exit(0);
  }
  readfd=open(FIFO1,O_RDONLY,0);
  writefd=open(FIFO2,O_WRONLY,0);
  printf("connection established...\n");
  read(readfd,fname,255);
  printf("Clinent has requested...%s\n",fname );
  fd=open(fname,O_RDONLY);
  if(fd<0)
  {
    strcpy(buffer,"FILE cannot be opened...");
    write(writefd,buffer,sizeof(buffer));
    exit(0);
  }
  else
  {
    while((n=read(fd,buffer,sizeof(buffer)))>0)
    {
      write(writefd,buffer,n);
    }
  }

  close(readfd);
  unlink(FIFO1);
  close(writefd);
  unlink(FIFO2);

}
