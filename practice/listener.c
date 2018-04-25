#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<time.h>

#define HELLO_PORT 1337
#define HELLO_GROUP "255.0.0.38"
#define MSGBUFSIZE 256

int main()
{
  struct sockaddr_in addr;
  int create_socket,n,addrlen;
  struct ip_mreq mreq;
  char msgbuf[MSGBUFSIZE];
  int yes = 1;
  if(create_socket=socket(AF_INET,SOCK_DGRAM,0)<0)
  {
    printf("Socket creation failed....\n");
    exit(0);
  }
  if(setsockopt(create_socket,SOL_SOCKET,SO_REUSEADDR,(char *)&yes,sizeof(yes)))
  {
    printf("reuse address failed....\n");
    exit(0);
  }
  memset(&addr,0,sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr =htonl(INADDR_ANY);
  addr.sin_port= htons(HELLO_PORT);

  if(bind(create_socket,(struct sockaddr*)&addr,sizeof(addr)))
  {
    printf("binding failed...\n");
    exit(0);
  }

  mreq.imr_multiaddr.s_addr = inet_addr(HELLO_GROUP);
  mreq.imr_interface.s_addr = htonl(INADDR_ANY);
//  if((setsockopt(create_socket,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)))<0)
  if(setsockopt(create_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&mreq, sizeof(mreq))<0)
  {
  //  printf("%d\n",errno);
    printf("set socket failed...\n");
    exit(0);
  }

  while(1){
    addrlen=sizeof(addr);
    if((n=recvfrom(create_socket,msgbuf,sizeof(msgbuf),0,(struct sockaddr*)&addr,&addrlen))<0)
    {
      printf("recvfrom error...\n");
      exit(0);
    }
    msgbuf[n]='\0';
    printf("%s\n",msgbuf);
  }
}
