#include<stdio.h>
#define MAX 10
#define INF 999

struct rtable
{
  unsigned dist[MAX];
  unsigned from[MAX];
}rt[10];

void find(int a,int b)
{
  int x;
  x=rt[a].from[b];
  if(x==a)
    return;
  printf("%d->",x+1);
  find(x,b);
}

int main()
{
  int dm[MAX][MAX];
  int n,i,j,k,count=0,hop[10][10]={0},l=0;
 printf("\nEnter n:");
  scanf("%d",&n);
  printf("\nEnter adjacent matrix:\n");
  for(i=0;i<n;i++)
   for(j=0;j<n;j++)
    {
        scanf("%d",&dm[i][j]);
           rt[i].dist[j]=dm[i][j];
           rt[i].from[j]=j;
    }

  for(i=0;i<n;i++)
  {
   for(j=0;j<n;j++)
    {
    for(k=0;k<n;k++)
     {
       if(rt[i].dist[j]>rt[i].dist[k]+rt[k].dist[j])
        {
         rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];
         rt[i].from[j]=k;
         count++;
         if(count==0)
           hop[i][j]=1;
         else
           hop[i][j]=count+hop[k][j];
        }
     } //k
  count=0;
    } //j
  } //i
  for(i=0;i<n;i++)
  {
   printf("\nfor node-%d\nNode\tVia node\tDist\tNo of hop",i);
       for(j=0;j<n;j++)
       {
        if(i==j)
          ;
        else
         printf("\n%d\t%d\t\t%d\t\t%d",j+1,rt[i].from[j]+1,rt[i].dist[j],hop[i][j]+1);
       }
  }
  printf("\nTo find path");
  printf("\nEnter source:");
  scanf("%d",&i);
  printf("Enter dest:");
  scanf("%d",&j);
  printf("\nPath is %d->",i);
  find(i-1,j-1);
  printf("%d\n",j);
  printf("\nDistance=%d",rt[i-1].dist[j-1]);
  return 0;
}
