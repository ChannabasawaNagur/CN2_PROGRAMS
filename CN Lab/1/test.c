#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

char buffer[1000];

void client(int read_fd, int write_fd)
{
  printf("Enter the file name\n");
  fflush(stdout);
  fgets(buffer, sizeof(buffer), stdin);

  write(write_fd, buffer, sizeof(buffer));

  while((read(read_fd, buffer, sizeof(buffer))>0))
    printf("%s",buffer);
}

void server(int read_fd, int write_fd)
{
  FILE *fp;
  char line[1000];
  read(read_fd, buffer, sizeof(buffer));

  if (strchr(buffer, '\n'))
    *strchr(buffer, '\n')=0;

  fp = fopen(buffer, "r");

  if (fp==NULL)
  {
    strcpy(buffer, "Can't open file\n");
    write(write_fd, buffer, strlen(buffer));
    exit(1);
  }
  else
  {
    while(fgets(line, sizeof(line), fp)!=NULL)
      write(write_fd, line, sizeof(line));
    printf("%s\n", "SUCCESSFUL");
  }
}

int main()
{
  int pip1[2], pip2[2];
  int status;
  int c;
  pipe(pip1);
  pipe(pip2);
  c = fork();

  if (c>0)
  {
    close(pip1[0]);
    close(pip2[1]);

    client(pip2[0], pip1[1]);
    wait(&status);
  }
  else
  {
    close(pip1[1]);
    close(pip2[0]);

    server(pip1[0], pip2[1]);
  }

  return 0;
}
