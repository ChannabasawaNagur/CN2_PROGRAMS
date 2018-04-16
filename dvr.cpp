#include<bits/stdc++.h>
using namespace std;

int d[100][100];

int parent[100];

int main()
{
    int n;
    cout<<"enter the no. nodes:\n";
    cin>>n;
    cout<<"enter distance vector graph\n";
    for(int i=1;i<=n;i++)
    {
      for(int j=1;j<=n;j++)
      {
        cin>>d[i][j];
        if(i==j)
          d[i][j]=0;
        if(d[i][j]!=0 && d[i][j]!=999)
          parent[j]=i;
      }
    }

    for(int i=1;i<=n;i++)
    {
      for(int j=1;j<=n;j++)
      {
        for(int k=1;k<=n;k++)
        {
          if(d[i][j]>d[i][k]+d[k][j])
          {
            d[i][j]=d[i][k]+d[k][j];
            parent[j]=k;
          }
        }
      }
    }

    for(int i=1;i<=n;i++)
    {
      for(int j=1;j<=n;j++)
      {
        cout<<d[i][j]<<" ";
      }
      cout<<endl;
    }

}
