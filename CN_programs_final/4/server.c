#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
  int cont, create_socket, new_socket, fd,addrlen;
  int buf_length = 2048;
  char fname[256];
  char *buffer;
  buffer = malloc(buf_length);
  struct sockaddr_in address;
  if((create_socket=socket(AF_INET,SOCK_STREAM,0))>0)
  printf("Socket created....\n");
  address.sin_family = AF_INET;
  address.sin_port = htons(15000);
  address.sin_addr.s_addr = INADDR_ANY;
  if(bind(create_socket,(struct sockaddr *)&address,sizeof(address))==0)
    printf("Binding socket successfull....\n");
  listen(create_socket,3);
  addrlen = sizeof(struct sockaddr_in);
  new_socket = accept(create_socket,(struct sockaddr *)&address, &addrlen);
  if(new_socket>0)
    printf("the client has connected....waiting for request....\n");
  else
  {
    printf("error in accepting ....%d",new_socket);
  }
  recv(new_socket,fname,255,0);
  fd=open(fname,O_RDONLY);
  if(fd<0)
  {
    printf("error in opening file....\n");
    return 0;
  }
  else
  {
    while((cont=read(fd,buffer,buf_length))>0)
      send(new_socket,buffer,cont,0);
  }
  printf("Request completed...\n");
  close(new_socket);
  return close(create_socket);
}
