#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
int bs;

int leaky(int a,int b)
{
  if(a>bs)
  {
    cout<<"Bucket overflow...\n";
  }
  else
  {
    while(a>b)
    {
      cout<<b <<"  bytes outputted....\n";
      a-=b;
    }
    if(a>0)
    {
      cout<<a <<"  remaining bytes outputted...\n";
    }
    cout<<"packet transfer complete...\n";
  }
  return 0;
}

int main()
{
  int ps,o;
  cout<<"enter bucket size:\n";
  cin>>bs;
  cout<<"o/p rate:\n";
  cin>>o;
  cout<<"enter packet size:\n";
  cin>>ps;
  leaky(ps,o);

}
