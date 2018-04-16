#include<stdio.h>
#include<math.h>
#define MAX 50
void checks(int);
main()
{
 int nums[MAX],ch;
 while(1)
 {
  printf("choose no of bits\n1) 8-bit\n2) 12-bit\n3) 16-bit\n");
  scanf("%d",&ch);
  switch(ch)
  {
   case 1: checks(8); break;
   case 2: checks(12); break;
   case 3: checks(16); break;
   default: return 0;
  }
 }
  return 0;
}

void checks(int bits)
{
    int j,lim,input[MAX],in=0,i=0,checksum=0;
    long int sum=0;
    lim=pow(2,bits);
    printf("---AT SENDER---\n");
    printf("enter %d-bit input values (in the range 0 to %d)\n",bits,lim-1);
   // sum+=checksum;
    for(i=0;in<lim;i++)
    {
        scanf("%d",&in);
        input[i]=in;
    }
    for(j=0;j<i-1;j++) //i-1 because last val > lim also taken
        sum+=input[j];
    checksum=lim-1-(sum%(lim-1)); //sum%(lin-1) --> wrap sum and (lim-1) - that --> 1's comp
    printf("checksum at sender=%d\n",checksum);
    printf("sent\n");
     for(j=0;j<i-1;j++)
       printf("%d\t",input[j]);
     printf("checksum=%d\n",checksum);

     input[i-1]=checksum;
     printf("---AT RECEIVER---\n");
     printf("Received data\n");
     for(j=0;j<i;j++)
        printf("%d\t",input[j]);
     checksum=sum=0;
     for(j=0;j<i;j++)
        sum+=input[j];
     checksum=sum%(lim-1);
     printf("checksum at receiver=%d\n",checksum);
     if(checksum==0)
        printf("no errors\n");
}

