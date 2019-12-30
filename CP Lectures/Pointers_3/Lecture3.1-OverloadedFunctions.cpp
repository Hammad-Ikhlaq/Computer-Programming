#include<iostream>
using namespace std;

//Test 1: Comment double Square(double x) and then test main()
//Test 2: Comment int Square(int x) and then test main()
//Test 3: Uncommnet both the functions and then test main()
int Square(int x)
{
	cout<<"\n\n\nI am Integer Function.\n";
	return x*x;
}
double Square(double x)
{
	cout<<"\n\n\nI am Double Function.\n";
	return x*x;
}
void main()
{
	int a = 5;
	cout<<"Calculating Square of "<<a<<endl;
	cout<<"Answer = \t"<<Square(a)<<endl;

	double b = 5.5;
	cout<<"\n\n\nCalculating Square of "<<b<<endl;
	cout<<"Answer = \t"<<Square(b)<<endl;	
}

