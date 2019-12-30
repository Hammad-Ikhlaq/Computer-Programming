#include<iostream>
using namespace std;

int* GetArrayFromUser(int& size)
{
	cout<<"\n\n\nI am inside GetArrayFromUser\n";
	cout<<"Enter size of Array:\t";
	cin>>size;
	int* tempArray = 0;
	if(size > 0)
	{
		tempArray = new int[size];
		for(int i = 0; i< size ; i++)
			tempArray[i] = i+1;
	}

	cout<<"tempArray is pointing to location:\t"<<tempArray<<endl;
	cout<<"Address of tempArray:\t"<<&tempArray<<endl;

	return tempArray;
}

void UpdateArray(int* intArray, const int& size)
{
	cout<<"\n\n\nI am inside UpdateArray\n";
	cout<<"intArray is pointing to location:\t"<<intArray<<endl;
	cout<<"Address of intArray:\t"<<&intArray<<endl;
	for(int i = 0; i< size ; i++)
			intArray[i] = intArray[i] * 2;
}

void DisplayArray(int* tempArray, const int& size)
{
	cout<<"\n\n\nI am inside DisplayArray\n";
	cout<<"tempArray is pointing to location:\t"<<tempArray<<endl;
	cout<<"Address of tempArray:\t"<<&tempArray<<endl;

	cout<<"\n\n\nData in Array:"<<endl;
	for(int i = 0; i< size ; i++)
	{
			cout<<"tempArray["<<i<<"]\t"<<tempArray[i]<<"\tAddress of tempArray["<<i<<"]\t\t"<<&tempArray[i]<<endl;
	}
}

void main()
{
	int size = 5;
	int* myArray = GetArrayFromUser(size);
	if (myArray != 0)		//Why do we need this check?
	{
		UpdateArray(myArray, size);
		DisplayArray(myArray, size);

		cout << "\n\n\nI am inside Main()\n";
		cout << "myArray is pointing to location:\t" << myArray << endl;
		cout << "Address of myArray:\t" << &myArray << endl;

		delete[] myArray;
	}
}