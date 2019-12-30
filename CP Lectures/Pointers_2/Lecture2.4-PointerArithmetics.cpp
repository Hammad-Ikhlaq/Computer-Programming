#include<iostream>
using namespace std;

void main()
{
	int size;

	cout<<"Enter size of array:\t";
	cin>>size;

	int* myArrayPtr = new int[size];	//Allocate memory

	int* temp = myArrayPtr;

	cout<<"\n\nValues in Array before and after initialization:\n\n";

	for(int i=0 ; i<size ; i++)		//Scalable
	{
		cout<<myArrayPtr[i];
		myArrayPtr[i] = i+1;
		cout<<"\t"<<myArrayPtr[i]<<endl;
	}

	cout<<"\n\nValues in Array before and after update:\n\n";
	for(int i=0 ; i<size ; i++)
	{
		cout<<*temp;
		*temp = (i+1)*5;
		cout<<"\t"<<*temp<<endl;
		temp++;		//Move the pointer to next integer
	}

	int index = 0;
	int* temp2 = myArrayPtr;

	cout<<"\n\nEnter the index which you want to read:\t";
	cin>>index;

	cout<<"\n\nValue saved at index "<<index<<" is :\t"<<*(temp2+index)<<endl;

	delete[] myArrayPtr;	//Deallocate Memory
}