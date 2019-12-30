#include<iostream>
using namespace std;

class A
{
private:
	int a;
protected:
	int protectedData;
public:
	A(int, int);

	void PrintInfo();
};
A::A(int temp1 = 10, int temp2 = 20)//Default Parameters
{
	cout << "A() Called.\n";
	a = temp1;
	protectedData = temp2;
}

void A::PrintInfo()
{
	cout << "a = " << a << endl;
	cout << "ProtectedData = " << protectedData << endl;
}

void main()
{
	A objA;
	objA.PrintInfo();

	cout << endl << endl << endl;

	A obj2(100, 200);
	obj2.PrintInfo();

	cout << endl << endl << endl;

	A obj3(1);
	obj3.PrintInfo();

	system("pause");
}