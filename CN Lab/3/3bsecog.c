#include<sys/types.h>
#include<sys/ipc.h> //msgget
#include<sys/msg.h> //msgget
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

int main()
{
        int msqid,fd,n,pid;
        char fcon[100]; //file contents
        struct
        {
                long mtype;
                char fname[20];
        }send,rec;
        while((msqid = msgget((key_t)10,IPC_CREAT|0666))==-1);
        pid = fork();
        if(pid == 0) //child
        {
                printf("child started");
                printf("Enter the filename with extension:\t");
                 scanf("%s",send.fname);
                msgsnd(msqid,&send,sizeof(send),0);
                printf("child ended\n");
        }
        else //parent
        {
                wait();
                printf("parent started");
                msgrcv(msqid,&rec,sizeof(rec),0,0);

                fd = open(rec.fname,O_RDONLY);
                n = read(fd,fcon,100);

                fcon[n]='\0';
                printf("the file contents are:\n%s",fcon);
                close(fd);
                printf("parent ended");
        }
        return 0;
}
