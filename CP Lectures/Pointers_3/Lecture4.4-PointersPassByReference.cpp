#include<iostream>
using namespace std;

void Swap(int* & a, int*& b)
{
	cout<<"\n\n\nInside Swap:\n";
	cout<<"Address of a:\t"<<&a<<endl;
	cout<<"Address of b:\t"<<&b<<endl;

	int* temp = a;
	a = b;
	b = temp;
}

int* GetArray()
{
	int size = 10;
	int* aPtr = new int[size];
	cout<<"\n\n\nInitialize and Print Array:\n";
	for(int i = 0 ; i < size ; i++)
	{
		aPtr[i] = i+1;
		cout<<aPtr[i]<<endl;

	}
	delete[] aPtr;
	return aPtr;
}
void main()
{
	int x = 5;
	int y = 10;
	int* xPtr = &x;
	int* yPtr = &y;

	cout<<"Original Values:\n";
	cout<<"Address of xPtr:\t"<<&xPtr<<endl;
	cout<<"Address of yPtr:\t"<<&yPtr<<endl;
	cout<<"*xPtr:\t"<<*xPtr<<endl;
	cout<<"*yPtr:\t"<<*yPtr<<endl;

	Swap(xPtr, yPtr);

	cout<<"Values after Swap():\n";
	cout<<"*xPtr:\t"<<*xPtr<<endl;
	cout<<"*yPtr:\t"<<*yPtr<<endl;

	int* myArray = GetArray();		//What went wrong in this function. Fix this issue.
	cout << "I am back in main()" << endl;
	cout<<"\n\n\nmyArray[0]:\t"<<myArray[0]<<endl;
	cout<<"myArray[5]:\t"<<myArray[5]<<endl;
	cout<<"myArray[9]:\t"<<myArray[9]<<endl;
}