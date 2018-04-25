#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#define MAX 1000
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
char fname[1000];
char buffer[1000];

int main()
{
  int readfd,writefd,n;
  printf("waiting for server to come online...\n");
  writefd=open(FIFO1,O_WRONLY);
  readfd=open(FIFO2,O_RDONLY);
  printf("enter the file to be  fetched...\n");
  scanf("%s",fname);
  write(writefd,fname,sizeof(fname));
  printf("waiting for server reply...\n");
  while((n=read(readfd,buffer,MAX))>0)
    write(1,buffer,n);
  close(writefd);
  unlink(FIFO1);
  close(readfd);
  unlink(FIFO2);
  return 0;
}
