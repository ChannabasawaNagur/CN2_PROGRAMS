#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>

#define HELLO_PORT 1337
#define HELLO_GROUP "255.0.0.38"

int main()
{
  int create_socket,cnt;
  struct sockaddr_in addr;
  struct ip_mreq mreq;
  char *message = "Hello,World!";

  if((create_socket=socket(AF_INET,SOCK_DGRAM,0))<0)
  {
    printf("socket creation failed...\n");
    exit(0);
  }
  memset(&addr,0,sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(HELLO_GROUP);
  addr.sin_port = htons(HELLO_PORT);

  while(1)
  {
    if(sendto(create_socket,message,strlen(message),0,(struct sockaddr*)&addr,sizeof(addr))<0)
    {
      printf("error in sending...\n");
      exit(0);
    }
    else
      puts("sent");
  }

}
