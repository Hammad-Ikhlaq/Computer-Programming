#include<iostream>
using namespace std;

void main()
{
	int a = 999;			// a is an integer
	int* aPtr = 0;		// aPtr is pointer to an integer
		
	// aPtr is a null pointer now...Pointing to nothing...check with aPtr = nullptr; as well
	
	cout<<"\n\n\nAfter Initialization...\n\n";
	cout<<"a =\t"<<a<<endl;
	cout<<"value in aPtr =\t"<<aPtr<<endl;
	
	//Pointing to specific data

	aPtr = &a;

	cout<<"\n\n\nAfter pointing to a ...\n\n";
	cout<<"Address of a =\t"<<&a<<endl;
	cout<<"Address of aPtr:\t"<<&aPtr<<endl;
	cout<<"value in aPtr =\t"<<aPtr<<endl;
	cout<<"a =\t"<<a<<endl;
	cout<<"*aPtr =\t"<<*aPtr<<endl;

	//Change the data of a and check what happens

	a = 10;

	cout<<"\n\n\nAfter changing a's data ...\n\n";
	cout<<"Address of a =\t"<<&a<<endl;
	cout<<"Address of aPtr:\t"<<&aPtr<<endl;
	cout<<"value in aPtr =\t"<<aPtr<<endl;
	cout<<"a =\t"<<a<<endl;
	cout<<"*aPtr =\t"<<*aPtr<<endl;

	//Changing data using pointer
	*aPtr = 500;

	cout<<"\n\n\nAfter changing a's data using aPtr ...\n\n";
	cout<<"Address of a =\t"<<&a<<endl;
	cout<<"Address of aPtr:\t"<<&aPtr<<endl;
	cout<<"value in aPtr =\t"<<aPtr<<endl;
	cout<<"a =\t"<<a<<endl;
	cout<<"*aPtr =\t"<<*aPtr<<endl;

	//Take data from user and then print

	cout<<"\n\n\nEnter value in a:\t";
	cin>>a;

	cout<<"\n\n\nAfter data input in a ...\n\n";
	cout<<"Address of a =\t"<<&a<<endl;
	cout<<"Address of aPtr:\t"<<&aPtr<<endl;
	cout<<"value in aPtr =\t"<<aPtr<<endl;
	cout<<"a =\t"<<a<<endl;
	cout<<"*aPtr =\t"<<*aPtr<<endl;


	cout<<"\n\n\nEnter value in *aPtr:\t";
	cin>>*aPtr;

	cout<<"\n\n\nAfter data input in aPtr ...\n\n";
	cout<<"Address of a =\t"<<&a<<endl;
	cout<<"Address of aPtr:\t"<<&aPtr<<endl;
	cout<<"value in aPtr =\t"<<aPtr<<endl;
	cout<<"a =\t"<<a<<endl;
	cout<<"*aPtr =\t"<<*aPtr<<endl;

	int b = 100;

	//aPtr is going to point b

	aPtr = &b;
	cout<<"\n\n\nAfter pointing to b ...\n\n";
	cout<<"Address of b =\t"<<&b<<endl;
	cout<<"Address of aPtr:\t"<<&aPtr<<endl;
	cout<<"value in aPtr =\t"<<aPtr<<endl;
	cout<<"a =\t"<<a<<endl;
	cout<<"b =\t"<<b<<endl;
	cout<<"*aPtr =\t"<<*aPtr<<endl;

	int* xyzVariable = aPtr;
	cout<<"\n\n\n xyzVariable ...\n\n";
	cout<<"Address of b =\t"<<&b<<endl;
	cout<<"Address of aPtr:\t"<<&aPtr<<endl;
	cout<<"Address of xyzVariable:\t"<<&xyzVariable<<endl;
	cout<<"value in aPtr =\t"<<aPtr<<endl;
	cout<<"value in xyzVariable =\t"<<xyzVariable<<endl;
	cout<<"a =\t"<<a<<endl;
	cout<<"b =\t"<<b<<endl;
	cout<<"*aPtr =\t"<<*aPtr<<endl;
	cout<<"*xyzVariable =\t"<<*xyzVariable<<endl;
}