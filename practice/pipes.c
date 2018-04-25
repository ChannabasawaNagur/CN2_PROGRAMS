#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
char buf[10000];

void client(int readfd,int writefd)
{
  printf("enter filename to be fetched:\n");
  fflush(stdout);
  printf("asdfjasjf\n" );
  fgets(buf, sizeof(buf), stdin);
  printf("hehe\n" );
  write(writefd,buf,sizeof(buf));
  printf("haha" );
  while((read(readfd,buf,sizeof(buf)))>0)
  printf("%s",buf);
}

void server(int readfd,int writefd)
{
  char line[10000];
  printf("server online\n");
  read(readfd,buf,strlen(buf));
  FILE *fp;
  if(strchr(buf,'\n'))
  {
    *strchr(buf,'\n')=0;
  }
  fp=fopen(buf,"r");
  if(fp==NULL)
  {
      strcpy(buf,"file cannot open\n");
    write(writefd,buf,strlen(buf));
    exit(1);
  }
  else
  {
    while(fgets(line,sizeof(line),fp)!=NULL)
    write(writefd,line,sizeof(line));
    printf("%s",line);
  }
}

int main()
{
  int pipe1[2],pipe2[2];
  int child;
  int status;
  pipe(pipe1);
  pipe(pipe2);
  printf("child process :");
  child=fork();
  if(child>0)
  {
    close(pipe1[0]);
    close(pipe2[1]);
    client(pipe2[0],pipe1[1]);
    wait(&status);
    printf("chient executed\n");
  }
  else
  {
    close(pipe1[1]);
    close(pipe2[0]);
    server(pipe1[0],pipe2[1]);
    printf("server executed successfully\n");
  }
  return 0;
}
