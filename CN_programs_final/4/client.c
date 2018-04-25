#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
  int buf_length = 2048;
  int cont,create_socket,fd;
  char fname[256];
  struct sockaddr_in address;
  char *buffer;
  buffer = malloc(buf_length);
  if((create_socket=socket(AF_INET,SOCK_STREAM,0))>0)
      printf("Socket created successfully.....\n");
  address.sin_family = AF_INET;
  address.sin_port = htons(15000);
  inet_pton(AF_INET,argv[1],&address.sin_addr);
  if(connect(create_socket,(struct sockaddr*)&address,sizeof(address))==0)
    printf("Client connected to server....\n");
  printf("enter the file name to be received...\n");
  scanf("%s",fname);
  send(create_socket,fname,sizeof(fname),0);
  printf("request sent successfully....\n waiting for reply....\n");
  while((cont=recv(create_socket,buffer,buf_length,0))>0)
    write(1,buffer,cont);

  return close(create_socket);
}
