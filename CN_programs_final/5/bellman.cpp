#include<iostream>
#include<stdlib.h>
using namespace std;

struct node{
  int dist[20];
  int from[20];
}route[10];

int dvr(int source,int dest)
{
  int mid= route[source-1].from[dest-1] + 1;
  cout<<"->"<<mid;
  if(mid==source)
  {
    cout<<"\n";
    exit(0);
  }
  else
    dvr(mid,dest);
}

int main()
{
  int n;
  cin>>n;
  int dm[20][20];
  int i,j,source,dest,k;
  for(i=0;i<n;i++)
  {
    for(j=0;j<n;j++)
    {
      cin>>dm[i][j];
      if(i==j)
        dm[i][j]=0;
      route[i].dist[j]=dm[i][j];
      route[i].from[j]=j;
    }
  }
  int flag;
  do{
    flag=0;
    for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
      {
        for(k=0;k<n;k++)
        {
          if(route[i].dist[j]> route[i].dist[k]+route[k].dist[j])
          {
            route[i].dist[j]=route[i].dist[k]+route[k].dist[j];
            route[i].from[j]=k;
            flag=1;
          }
        }
      }
    }
  }while(flag);

  for(i=0;i<n;i++)
  {
    cout<<"Router:"<<i+1<<endl;
    cout<<"dest\t"<<"next_hop\t"<<"dist\n";
    for(j=0;j<n;j++)
    {
      cout<<j+1<<"\t"<<route[i].from[j]+1<<"\t"<<route[i].dist[j]<<"\n";
    }
    cout<<endl;
  }

  cout<<"enter the source and dest...\n";
  cin>>source>>dest;
  cout<<source;
  dvr(source,dest);

}
