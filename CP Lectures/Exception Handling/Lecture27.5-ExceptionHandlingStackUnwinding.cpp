#include<iostream>
#include<stdexcept>
using namespace std;

void Function3()
{
	cout << "I am in Function 3.\n";

	throw runtime_error("Runtime error occured in Function 3.\n");

	cout << "I am going from Function 3.\n";
}

void Function2()
{
	cout << "I am in Function 2. Going to call Function 3\n";

	Function3();

	cout << "I am going from Function 2.\n";
}

void Function1()
{
	cout << "I am in Function 1. Going to call Function2\n";

	Function2();

	cout << "I am going from Function 1.\n";
}

void main()
{
	try
	{
		cout << "I am in Main(). Going to call Function 1.\n";
		Function1();
		cout << "I am back from Function 1.\n";
	}
	catch (runtime_error& ex)
	{
		cout << "Exception occured:\t" << ex.what() << endl;
	}
}