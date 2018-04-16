#include<iostream> 
#include<unistd.h>
#define bucketSize 512 
void bktInput(int a,int b) 
{
	if (a > bucketSize)
		std::cout << "\n\t\tBucket overflow";
	else 
	{
	sleep(1);
	while (a > b) 
		{
			std::cout << "\n\t\t" << b << " bytes outputted.";
			a -= b;
			sleep(1);
		}
		if (a > 0)
			std::cout << "\n\t\tLast " << a << " bytes sent\t";
		std::cout << "\n\t\tBucket output successful\n\n";
	}
}
int main()
{
	int		op        , pktSize;
	std::cout << "Enter output rate : ";
	std::cin >> op;
	for (int i = 1; i <= 5; i++) {
		sleep(1);
		pktSize=rand()%800;
		std::cout << "\nPacket no " << i << "\tPacket size = " << pktSize;
		bktInput(pktSize, op);
	}
	return 0;
}
