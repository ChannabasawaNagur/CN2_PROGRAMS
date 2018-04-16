#include<stdio.h>
#include<string.h>

#define N strlen(g)
void xor();
void crc();
int l;
char dw[128], cs[128], g[]="10001000000100001";

void main()
{
 int i;
  printf("\nEnter dataword : ");
  scanf("%s",dw);
  printf("\nGenerating Polynomial is : %s",g);
  l=strlen(dw);
  for(i=l;i<l+N-1;i++)//appending zeros
    dw[i]='0';
  printf("\nModified dataword is :  %s",dw);
  crc();
  printf("\nChecksum is : %s",cs);
  for(i=l;i<l+N-1;i++)
    dw[i]=cs[i-l];
  printf("\nFinal Codeword is : %s",dw);
  printf("\nTest Error detection 0(yes) 1(no) ? : ");
  scanf("%d",&i);
  if(i==0)
  {
    printf("Enter position where error is to inserted : ");
    scanf("%d",&i);
    dw[i]=(dw[i]=='0')?'1':'0';
    printf("Errorneous data   : %s\n",dw);
  }
  crc();
  for (i=0;(i<N-1)&&(cs[i]!='1');i++);
if(i<N-1)
    printf("Error detected.");
else
    printf("No Error Detected.");
}

void xor()
{
 int i;
  for(i=1;i<N;i++)
    cs[i]=((cs[i]==g[i])?'0':'1');
}

void crc()
{
  int i,j;
  for(i=0;i<N;i++)
    cs[i]=dw[i];
  do
  {
    if(cs[0]=='1')
       xor();
    for(j=0;j<N-1;j++) // 0-15 -> 16 bits
      cs[j]=cs[j+1];
    cs[j]=dw[i++];
  }while(i<=l+N-1);
}
