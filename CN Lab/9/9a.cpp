#include<iostream>
//#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
char data[5];
int encoded[8], edata[7], syndrome[3];
int hmatrix[3][7]= { 1,0,0,0,1,1,1,
         		   0,1,0,1,0,1,1,
		         0,0,1,1,1,0,1};
char gmatrix[4][8]={ "0111000", "1010100", "1100010", "1110001"};
int main() {
  int i,j;
  std::cout<<"Hamming Code --- Encoding\n";
  std::cout<<"Enter 4 bit data : ";
  std::cin>>data;
  std::cout<<"Generator Matrix\n";
  for(i=0;i<4;i++) std::cout<<"\t"<<gmatrix[i]<<"\n";
  std::cout<<"Encoded Data : ";
  for(i=0;i<7;i++) {
    for(j=0;j<4;j++) 
      encoded[i]+=((data[j]- '0')*(gmatrix[j][i]- '0'));
    encoded[i]=encoded[i]%2;
    std::cout<<encoded[i]<<" ";
  }
  std::cout<<"\nHamming code --- Decoding\n";
  std::cout<<"Enter Encoded bits as received : ";
  for(i=0;i<7;i++) std::cin>>edata[i];
  for(i=0;i<3;i++) {
    for(j=0;j<7;j++)
      syndrome[i]=syndrome[i]+(edata[j]*hmatrix[i][j]);
    syndrome[i]=syndrome[i]%2;
  }
  for(j=0;j<7;j++)
    if ((syndrome[0]==hmatrix[0][j])&&(syndrome[1]==hmatrix[1][j])&&
	(syndrome[2]==hmatrix[2][j]))
      break;
  if(j==7)
    std::cout<<"Data is error free!!\n";
  else {
    std::cout<<"Error received at bit number "<<j+1<<" of the data\n";
    //edata[j]=!edata[j];
    std::cout<<"The Correct data Should be : ";
    for(i=0;i<7;i++) std::cout<<edata[i]<<" ";
    }
  return 0;
  }

