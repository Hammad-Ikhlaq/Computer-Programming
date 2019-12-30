#include<iostream>
using namespace std;

void main()
{
	int bArray[5] = {1,2,3,4,5};
	int* bPtr = bArray;

	cout<<"bArray:\t"<<bArray<<endl;
	cout<<"&bArray[0]:\t"<<&bArray[0]<<endl;
	cout<<"bPtr:\t"<<bPtr<<endl;

	cout<<"\n\n\nDisplay Elements:\n";
	for(int* temp = bPtr ; temp < bPtr+5 ; temp++)
	{
		cout<<*temp<<endl;
	}
}