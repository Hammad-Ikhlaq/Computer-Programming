#include<iostream>
#include<exception>
using namespace std;

class A
{
public:
	A(){ cout << "A() called.\n"; }
	~A(){ cout << "~A() called.\n"; }
};

void TestFunction()
{
	cout << "Inside TestFunction().\n";
	A a;
	A* aptr = new A();
	
	cout << "Going to throw exception.\n";
	throw exception();	
	cout << "This line will not be executed.\n";
		
}

void main()
{

	try
	{
		cout << "Calling TestFunction()\n";		
		TestFunction();
		cout << "Control will not return here.\n";
		
	}
	catch (exception&)
	{
		cout << "Exception hendled here" << endl;
	}
}