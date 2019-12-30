#include<iostream>
using namespace std;

void main()
{
	int size = 5;

	cout<<"Enter size of array:\t";
	cin>>size;

	int myArray[size];	//syntax error: size must be a constant. Make it constant to run program successfully.

	for(int i=0 ; i<5 ; i++)
		cout<<myArray[i]<<endl;
}