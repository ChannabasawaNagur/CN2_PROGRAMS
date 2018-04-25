#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>
#include<sys/socket.h>
#include<string.h>

#define HELLO_PORT 1337
#define HELLO_GROUP "225.0.0.38"

int main()
{
  int fd;
  struct sockaddr_in addr;
  addr.sin_family  = AF_INET;
  addr.sin_addr.s_addr = inet_addr(HELLO_GROUP);
  addr.sin_port = htons(HELLO_PORT);

  if((fd=socket(AF_INET,SOCK_DGRAM,0))<0)
  {
    printf("error in creating socket...\n");
    exit(0);
  }
  char *msg ="hello there!";

  while(1)
  {
    int addrlen=sizeof(addr);
    sendto(fd,msg,strlen(msg),0,(struct sockaddr*)&addr , addrlen);
    printf("sent...\n");
  }
  return 0;

}
