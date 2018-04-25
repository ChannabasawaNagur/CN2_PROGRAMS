#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#define MAX 1000
char buffer[1000];

void client(int readfd,int writefd)
{
  printf("enter the file to be requested....\n");
  scanf("%s",buffer);
  write(writefd,buffer,sizeof(buffer));
  while((read(readfd,buffer,MAX))>0)
  {
    printf("%s",buffer );

  }
}

void server(int readfd,int writefd)
{

    FILE *fp;
    char line[1000];
    read(readfd, buffer, sizeof(buffer));
    if( strchr( buffer, '\n' ) )
  		*strchr( buffer, '\n' ) = 0;
      fp=fopen(buffer,"r");
      if(fp==NULL)
      {
        strcpy(buffer,"file cannot be opened....");
        write(writefd,buffer,sizeof(buffer));
        exit(1);
      }
      else
      {
        while((fgets(line,sizeof(line),fp))!=NULL)
        {
          write(writefd,line,sizeof(line));
        }

      }
      printf("Transfer complete...\n");
}

int main()
{
  int pipe1[2],pipe2[2];
  pipe(pipe1);
  pipe(pipe2);
  int child;
  int status;
  printf("child process...\n");
  child=fork();
  if(child>0)
  {
    close(pipe1[1]);
    close(pipe2[0]);
    client(pipe1[0],pipe2[1]);
    wait(&status);
    exit(0);
  }
  else
  {
    close(pipe1[0]);
    close(pipe2[1]);
    server(pipe2[0],pipe1[1]);
    exit(0);
  }
  return 0;
}
