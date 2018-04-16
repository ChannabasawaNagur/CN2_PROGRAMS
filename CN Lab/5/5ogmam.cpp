//#include <conio.h>
#include<iostream>
//using namespace std;
#define MAX 10
int n;
class router {
    char adj_new[MAX],   adj_old[MAX];
    int  table_new[MAX], table_old[MAX];
  public:
    
void build(int );
    router(){
      for(int i=0;i<MAX;i++) table_old[i]=table_new[i]=99;

    }
    void copy(){
      for(int i=0;i<n;i++) {
        adj_old[i]  =adj_new[i];
        table_old[i]=table_new[i];
      }
    }

    int equal() {
      for(int i=0;i<n;i++)
        if(table_old[i]!=table_new[i]||adj_new[i]!=adj_old[i])return 0;
      return 1;
    }
    void input(int j) {
      std::cout<<"Enter 1 if the corresponding router is adjacent to router"
          <<(char)('A'+j)<<" else enter 99: "<<std::endl<<"             ";
      for(int i=0;i<n;i++) 
        if(i!=j) std::cout<<(char)('A'+i)<<" ";
      std::cout<<"\nEnter matrix:";
      for(int i=0;i<n;i++) {
        if(i==j)
          table_new[i]=0;
        else
          std::cin>>table_new[i];
        adj_new[i]= (char)('A'+i);
      }
      std::cout<<std::endl;
    }

    void display(){
      std::cout<<"\nDestination Router: ";
      for(int i=0;i<n;i++) std::cout<<(char)('A'+i)<<" ";
      std::cout<<"\nOutgoing Line:      ";
      for(int i=0;i<n;i++) std::cout<<adj_new[i]<<" ";
      std::cout<<"\nHop Count:          ";
      for(int i=0;i<n;i++) std::cout<<table_new[i]<<" ";
    }

} r[10];

void router:: build(int j) {
      for(int i=0;i<n;i++)
        for(int k=0;(i!=j)&&(k<n);k++)
          if(table_old[i]!=99)
            if((table_new[i]+r[i].table_new[k])<table_new[k]) {
              table_new[k]=table_new[i]+r[i].table_new[k];
              adj_new[k]=(char)('A'+i);
            }
    }

void build_table() {
  int i=0, j=0;
  while(i!=n) {
    for(i=j;i<n;i++) {
      r[i].copy();
      r[i].build(i);
    }
    for(i=0;i<n;i++) 
      if(!r[i].equal()) {
        j=i;
        break;
      }
  }
}

int main() {
 // clrscr();
  std::cout<<"Enter the number the routers(<"<<MAX<<"): "; std::cin>>n;
  for(int i=0;i<n;i++) r[i].input(i);
  build_table();
  for(int i=0;i<n;i++) {
    std::cout<<"Router Table entries for router "<<(char)('A'+i)<<":-";
    r[i].display();
    std::cout<<std::endl<<std::endl;
  }
  return 0;
//  getch();
}

