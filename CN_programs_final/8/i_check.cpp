#include<iostream>
#include<stdio.h>
using namespace std;

unsigned short check(unsigned short checksum = 0)
{
  unsigned short int field[9];
  int sum = checksum;
  for(int i=0;i<9;i++)
  {
    scanf("%x",&field[i]);
    sum += (unsigned short) field[i];
    while(sum>>16)
      sum = (sum & 0x0FFFF) + (sum>>16);
  }
//  cout<<sum<<endl;
  sum = ~sum;
  return (unsigned short)sum;
}

int main()
{
  unsigned short checksum,res;
  cout<<"Sender:"<<endl;
  checksum=check();
  printf("%x\n",checksum);
  cout<<"Receiver:"<<endl;
  res=check(checksum);
  if(res==0)
  {
    cout<<"No error in transmission...\n";
    return 0;
  }
  else
  {
    cout<<"Error in transmission...\n";
    return 0;
  }
  return 0;

}
