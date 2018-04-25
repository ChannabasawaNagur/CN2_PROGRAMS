#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/stat.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(int argc,char *argv[])
{
  int create_socket,cont;
  int bufsize=1024;
  char * buffer = malloc(bufsize);
  char fname[256];
  struct sockaddr_in address;
  if((create_socket=socket(AF_INET,SOCK_STREAM,0))>0)
  {
    printf("socket created successfully\n");
  }
  address.sin_family=AF_INET;
  address.sin_port=htons(15000);
  inet_pton(AF_INET,argv[1],&address.sin_addr);
  if(connect(create_socket,(struct sockaddr*) &address,sizeof(address))==0)
  {
    printf("the connection was established...\n");
  }
  printf("enter the file ....");
  scanf("%s",fname);
  send(create_socket,fname,sizeof(fname),0);
  printf("request accepted....\n");
  while((cont=recv(create_socket,buffer,bufsize,0))>0)
  {
    write(1,buffer,cont);
  }
  printf("completed....");
  return close(create_socket);
}
