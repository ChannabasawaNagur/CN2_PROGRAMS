#include<stdio.h>
void dijkstra(int n,int cost[10][10],int source,int dest,int d[],int p[]);
void print_path(int source,int destination,int d[],int p[]);

int main()
{
   // freopen("input.txt","r",stdin);
    int n,a[10][10],i,j,d[10],p[10],s[10];
    printf("\n ENTER THE NO.OF NODES: ");
    scanf("%d",&n);
    printf("\n ENTER THE MATRIX ELEMENTS: ");
    for(i=0; i<n; i++)
    {
        printf("\nENTER THE DISTANCE FOR NODE:%d\n",i+1);
        for(j=0; j<n; j++)
            scanf("%d",&a[i][j]);
    }
    for(i=0; i<n && printf("\n"); i++)
    {
        for(j=0; j<n; j++)
            printf("%d ", a[i][j]);
    }

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            dijkstra(n,a,i,j,d,p);
            if(d[j]==9999)
                printf("%d not reachable from %d",j,i);
            else
            {
                printf("The shortest path and distance is shown below\n");
                print_path(i,j,d,p);
            }
        }
    }
    return 0;
}

void dijkstra(int n,int cost[10][10],int source,int dest,int d[],int p[])
{
    int s[10];
    int i,j,u,v,min;

    for(i=0; i<n; i++)
    {
        d[i]=cost[source][i];
        s[i]=0;
        p[i]=source;
    }

    s[source]=1;

    for(i=1; i<n; i++)
    {
        min=9999;
        u=-1;
        for(j=0; j<n; j++)
        {
              if(s[j]==0)
              {
                  if(d[j]<min)
                  {
                    min=d[j];
                    u=j;
                  }
              }
        }
        if(u==-1)
          return;

        s[u]=1;

        if(u==dest)
          return;

            for(v=0; v<n; v++)
            {
                if(s[v]==0)
                {
                    if(d[u]+cost[u][v]<d[v])
                    {
                        d[v]=d[u]+cost[u][v];
                        p[v]=u;
                    }
                }
            }
        }
}

void print_path(int source,int destination,int d[],int p[])
{
    int b;
    b=destination;
    while(b!=source)
    {
        printf("%d<-",b);
        b=p[b];
    }
    printf("%d = %d \n",b,d[destination]);
}

