#include<bits/stdc++.h>
using namespace std;

struct nodes{
  int dist[10];
  int from[10];
}rt[10];

void dvr(int source,int dest)
{
  int mid = rt[source-1].from[dest-1]+1;
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
  int dm[n][n];
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      cin>>dm[i][j];
      rt[i].dist[j]=dm[i][j];
      rt[i].from[j]=j;
    }
  }

  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      for(int k=0;k<n;k++)
      {
        if(rt[i].dist[j]>rt[i].dist[k]+rt[k].dist[j])
        {
          rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];
          rt[i].from[j]=k;
        }
      }
    }
  }

  for(int i=0;i<n;i++)
  {
    cout<<"Router:"<<i<<endl;
    cout<<"to\tnext_hop\tdist\n";
    for(int j=0;j<n;j++)
    {
      if(i==j)
        cout<<"-\t-\t-\n";
      else
        cout<<j<<"\t"<<rt[i].from[j]<<"\t"<<rt[i].dist[j]<<endl;
    }
  }

  int source,dest;
  cin>>source>>dest;
  cout<<source;
  dvr(source,dest);



}
