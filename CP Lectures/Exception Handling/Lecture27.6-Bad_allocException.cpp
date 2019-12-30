#include<iostream>
using namespace std;

void main()
{
	int* ptr[50];

	try
	{
		for (int i = 0; i < 50; i++)
		{
			ptr[i] = new int[50000000];
			cout << "Memory allocated.\n";
		}
	}
	catch (bad_alloc& memoryAllocationException)
	{
		cerr << "Exception occured:\t" << memoryAllocationException.what() << endl;
	}
}