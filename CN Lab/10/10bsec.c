#include<stdio.h>
#include<stdlib.h>

int min(int item1,int item2);

int  main()
{
int drop=0,count=0,minimum,packetsec,capcity;
int packet[25],process,i;                         // clearing screen
printf("enter bucket size");  //bucket size
    scanf("%d",&capcity);
printf("enter operation rate\n"); //opration rate,time to reach destination from temporary node
    scanf("%d",&process);
printf("enter no of sec to simulate\n");// to see what happens to the bucket
    scanf("%d",&packetsec);
for(i=0;i<packetsec;i++)
{
    printf("\n enter size of packet entering %d sec",i+1);
        scanf("%d",&packet[i]);
}
printf("second/packet received/packet sent/packet left/packet dropped\n");
        for(i=0;i<packetsec;i++)
        {
            count+=packet[i];
            if(count>capcity)
            {
                drop=count-capcity;
                count=capcity;
            }
            printf("%d",i+1); //sec
            printf("\t %d",packet[i]); //pkt recvd
            minimum=min(count,process);
            printf("\t\t%d",minimum); //pkt sent
            count=count-minimum;
            printf("\t\t%d",count); //pkt left
            printf("\t\t%d",drop); //drop
            drop=0;
            printf("\n");
        }
   /* for(;count!=0;i++);
    {
        if(count>capcity)
        {
            drop=count-capcity;
            count=capcity;
        }
        printf("%d",i+1); //sec
        printf("\t:0"); // pkt recvd
        minimum=min(count,process);
        printf("\t\t%d",minimum); //pkt sent
        count=count-minimum;
        printf("\t\t%d",count); //pkt left
        printf("\t\t%d",drop); //pkt dropped
    } */
return EXIT_SUCCESS; //return 0;
}

int min(int item1,int item2)
{
    if(item1<item2)
        return item1;
    else
        return item2;
}

