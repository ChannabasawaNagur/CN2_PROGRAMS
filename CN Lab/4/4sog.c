#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#define SERV_HOST_ADDR "127.0.0.1"
#define SERV_TCP_PORT 6886

extern int errno;
int
main ()
{
  int socktel, newsocktel, client;
  struct sockaddr_in cli_addr, serv_addr;
  char filename[30], buff[1002];
  int n, m;
  m = 0;
  int fd;
  if ((socktel = socket (AF_INET, SOCK_STREAM, 0)) < 0)
      perror ("socket open error:");
  printf ("server:stream socket open successfully\n");
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htons (INADDR_ANY);
  serv_addr.sin_port = htons (SERV_TCP_PORT);
  if (bind (socktel, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0)
      perror ("binding error:");
 else
    {
      printf ("\nserver : waiting for client\n");
      listen (socktel, SERV_TCP_PORT);
      for (;;)
      {
      client = sizeof (struct sockaddr_in);
      newsocktel =
        accept (socktel, (struct sockaddr *) &cli_addr, &client);
      if (newsocktel < 0)
        {
          perror ("new connection error\n");
          exit (1);
        }
      else
        {
          printf ("server:accept new connection\n");
          n = read (newsocktel, filename, 28);
          filename[n] = '\0';
          fd = open (filename, O_RDONLY);
          if (fd >= 0)
          {
          printf ("server:file %s found ready to transfer", filename);
          n = read (fd, buff, 1000);
          buff[n] = '\0';
          write (newsocktel, buff, n);
          printf ("\ntransfer complete\n");
          }
          else
            printf ("server : file %s not found\n", filename);
          close (newsocktel);
          printf ("closing the connection\n");
          exit (0);
        }
    }
    }
}
