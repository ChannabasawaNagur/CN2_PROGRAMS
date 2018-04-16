#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#define SERV_HOST_ADDR "127.0.0.1"
#define SERV_TCP_PORT 6886
int main ()
{
  int socktel;
  struct sockaddr_in cli_addr, serv_addr;
  char filename[100], buff[1000];
  int n;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr (SERV_HOST_ADDR);
  serv_addr.sin_port = htons (SERV_TCP_PORT);
  if ((socktel = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    printf ("\nclient=cant open stream socket\n");
  else
    printf ("\nclient:stream socket opened successfully\n");
  if (connect (socktel, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) <
      0)
    {
      printf ("\nclient:stream cant connect to server\n");
      perror ("connect server");
    }
  else
    {
      printf ("\nclient:connected to server successfully\n");
      printf ("\nenter the filename to be displayed:");
      scanf ("%s", filename);
      write (socktel, filename, strlen (filename));
      printf ("filename transferred to server\n");
      n = read (socktel, buff, 1000);
      if (n < 0)
        printf ("error reading from socket");
      else if (n == 0)
        printf ("filename %s not found on server\n", filename);
      else
    {
      printf ("client:display contents of %s\n", filename);
      fputs (buff, stdout);
    }
      close (socktel);
      exit (0);
    }
}
