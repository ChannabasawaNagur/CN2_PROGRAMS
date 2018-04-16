#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define PERMS 0666
char buf[512];
char fname[255];

int main()
{
  int readfd,writefd;
  size_t n;
  printf("trying to connect\n");
  writefd=open(FIFO1,O_WRONLY,0);
  readfd=open(FIFO2,O_RDONLY,0);
  printf("connected\nenter file name to be accessed\n");
  scanf("%s",fname);
  write(writefd,fname,strlen(fname));
  while((n=read(readfd,buf,512))>0)
  write(1,buf,512);
  close(readfd);
  close(writefd);
}
