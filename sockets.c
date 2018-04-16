#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
  int create_socket,new_socket,fd,addrlen,cont;
  int bufsize=1024;
  char *buffer=malloc(bufsize);
  char fname[256];
  struct sockaddr_in address;
  if((create_socket=socket(AF_INET,SOCK_STREAM,0))>0)
    printf("socket created successfully\n");
  address.sin_family=AF_INET;
  address.sin_port=htons(15000);
  address.sin_addr.s_addr=INADDR_ANY;
  if(bind(create_socket,(struct sockaddr*) &address,sizeof(address))>0)
    printf("socket binding\n");
  listen(create_socket,3);
  addrlen=sizeof(struct sockaddr_in);
  new_socket=accept(create_socket,(struct sockaddr*)&address,&addrlen);
  if(new_socket>0)
    printf("the client connection established...\n");
    recv(new_socket,fname,255,0);
    printf("the client has requeste file %s",fname);
    if((fd=open(fname,O_RDONLY))>0)
    {
      while((cont=read(fd,buffer,bufsize))>0)
      {
        send(new_socket,buffer,cont,0);
      }
    }
    else
    {
      printf("file couldnot be found\n");
      return 0;
    }
    printf("request completed...\n");
    close(new_socket);
    return close(create_socket);
}
