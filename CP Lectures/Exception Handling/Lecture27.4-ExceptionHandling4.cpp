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
	
	try
	{
		cout << "Going to throw exception.\n";
		throw exception("Something went wrong in TestFunction.");
		cout << "This line will not be executed.\n";
	}
	catch (exception& ex) // We have exception object with us
	{
		cout << "Exception Caught. Going to rethrow the exception after freeing the resources.\n";
		delete aptr;
		throw ex;	//rethrow
		cout << "This line will not be executed.\n";
	}
}

void main()
{

	try
	{
		cout << "Calling TestFunction()\n";		
		TestFunction();
		cout << "Control will not return here.\n";
		
	}
	catch (exception& ex1)
	{
		cout << "Exception occured:\t"<< ex1.what() << endl;
		//We have exception details now.
	}
}