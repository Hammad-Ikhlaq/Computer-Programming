#include<iostream>
using namespace std;

void main()
{
	int size = 5;

	cout<<"Enter size of array:\t";
	cin>>size;

	int* myArrayPtr = new int[size];	//Allocate memory
	
	cout << "\n\nAddress of size:\t" << &size << endl;
	cout << "\n\nAddress of myArrayPtr:\t" << &myArrayPtr << endl;
	cout << "\n\nAddress saved in myArrayPtr:\t" << myArrayPtr << endl;
	


	cout<<"\n\nValues in Array before and after initialization:\n\n";

	for(int i=0 ; i<size ; i++)		//Scalable
	{
		cout<<myArrayPtr[i];
		myArrayPtr[i] = i+1;
		cout<<"\t"<<myArrayPtr[i]<<endl;
	}

	cout<<"\n\nAddresses of Array Cells:\n\n";

	for(int i=0 ; i<size ; i++)		//Scalable
	{
		cout<<"Address of index "<<i<<":\t"<<&myArrayPtr[i]<<endl;
	}

	// We will cover following lines in next lecture.

	delete[] myArrayPtr;	//Deallocate Memory
	
}