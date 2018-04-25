#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define PERMS 0666
char buf[512];
char fname[255];

int main()
{
  int readfd,writefd,fd;
  size_t n;
  if(mkfifo(FIFO1,PERMS)<0)
    printf("fifo1 cannot be created\n");
  if(mkfifo(FIFO2,PERMS)<0)
    printf("CANT CREATE FIFO2\n");
  printf("waiting for request\n");
  readfd=open(FIFO1,O_RDONLY,0);
  writefd=open(FIFO2,O_WRONLY,0);
  printf("connectioon established\n");
  read(readfd,fname,255);
  if((fd=open(fname,O_RDWR))<0)
  {
    strcpy(buf,"cannot find file");
    write(writefd,buf,strlen(buf));
  }
  else
  {
    while((n=read(fd,buf,512))>0)
    write(writefd,buf,n);
  }
  close(readfd);
  unlink(FIFO1);
  close(writefd);
  unlink(FIFO2);
}
