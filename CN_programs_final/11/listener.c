#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define HELLO_PORT 1337
#define HELLO_GROUP "225.0.0.38"

int main()
{
  int fd;
  struct sockaddr_in addr;
  struct ip_mreq mreq;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(HELLO_PORT);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  char buf[1024];

  int yes=1;

  fd=socket(AF_INET,SOCK_DGRAM,0);
  if(fd<0)
  {
    printf("erro...\n");
    exit(0);
  }

  if(setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,(char *)&yes,sizeof(yes)))
  {
    printf("error in setsock...\n");
    exit(0);
  }

  if(bind(fd,(struct sockaddr*)&addr,sizeof(addr)))
  {
    printf("binding failed...\n");
    exit(0);
  }

  mreq.imr_multiaddr.s_addr = inet_addr(HELLO_GROUP);
  mreq.imr_interface.s_addr=htonl(INADDR_ANY);

  if(setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char *)&mreq,sizeof(mreq))<0)
  {
    printf("multicast error....\n");
    exit(0);
  }

  int addrlen,n;
  while(1)
  {
    addrlen=sizeof(addr);
    n=recvfrom(fd,buf,sizeof(buf),0,(struct sockaddr*)&addr,&addrlen);
    if(n<0)
    {
      printf("error..\n");
      exit(0);
    }
    else if(n==0)
    {
      break;
    }
    buf[n]='\0';
    printf("%s\n",buf);
  }
  return 0;


}
