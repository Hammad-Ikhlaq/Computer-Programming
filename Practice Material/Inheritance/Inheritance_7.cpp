#include<iostream>
using namespace std;

class A
{
	int a;
protected:
	int protectedData;
public:
	A();
	void PrintInfoA();
};
A::A()
{
	a = 10;
	protectedData = 100;
}

void A::PrintInfoA()
{
	cout << "a = " << a << endl;
	cout << "ProtectedData = " << protectedData << endl;
}
//----------------------------------------------------------------------------------
class B : A //Or private A // Inheritance is by default private if no member access specifier mentioned
{

	//Private data "a" is hidden.
	//protectedData is Private in Child Class
	//PrintInfoA() is Private in Child Class

	friend void SampleFriendFunction();
	int b;
public:
	B();
	void PrintInfoB();
};
B::B()
{
	protectedData = 200;	//Protected data of Parent is Private in Child. Accessible in Member Functions
	b = 20;
}
void B::PrintInfoB()
{
	PrintInfoA();	//Public of Parent is Private in Child. Accessible in Member Functions
	cout << "b = " << b << endl;
}

void SampleFriendFunction()
{
	cout << "I am SampleFriendFunction.\n";
	B objB;

	objB.PrintInfoA();		//Public of Parent is Private in Child. Accessible in Friend Functions

	cout << objB.protectedData << endl;	//Protected of Parent is Private in Child. Accessible in Friend Functions
}

void main()
{
	B objB;
	cout << endl << endl << endl;

	//objB.PrintInfoA(); //Public of Parent is Private in Child now. Not Accessible in Non Member Functions

	//cout << objB.protectedData << endl;	//Protected of Parent is Private in Child. Not Accessible in Non Member Functions



	cout << endl << endl << endl;

	SampleFriendFunction();

	cout << endl << endl << endl;

	system("pause");



}