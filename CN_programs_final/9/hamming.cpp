#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;

int main()
{
  int a[4],b[4],r[4],s[4];
  cout<<"enter the i/p\n";
  for(int i=3;i>=0;i--)
  {
    cin>>a[i];
  }
  r[0]= (a[2] + a[1] + a[0])%2;
  r[1]= (a[2] + a[1] + a[3])%2;
  r[2]= (a[0] + a[1] + a[3])%2;

  cout<<"7 bit hamming codeword is:\n";
  for(int i=3;i>=0;i--)
    cout<<a[i];
  for(int i=2;i>=0;i--)
    cout<<r[i];
  cout<<"enter the received 4 bit\n";
  for(int i=3;i>=0;i--)
  {
    cin>>b[i];
  }
  s[0]= (b[2] + b[1] + b[0] + r[0])%2;
  s[1]= (b[2] + b[1] + b[3] + r[1])%2;
  s[2]= (b[0] + b[1] + b[3] + r[2])%2;

  cout<<"syndrome is:\n";
  for(int i=2;i>=0;i--)
    cout<<s[i];
  if(s[2]==s[1]==s[0]==0)
    cout<<"no error in transmission..\n";
  else
    cout<<"error in transmission...\n";

    // errr bits correction .....(write a program to toggle that particular bit corresponding to below syndrome pattern)
    // 000 - no error
    // 001 -
    // 010 -
    // 011 - b2
    // 100 -
    // 101 - b0
    // 110 - b3
    // 111 - b1

}
