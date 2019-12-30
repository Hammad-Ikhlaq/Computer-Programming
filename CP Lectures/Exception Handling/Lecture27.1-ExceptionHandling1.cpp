#include<iostream>
#include<stdexcept>	//stdexcept header contains runtime_error
using namespace std;


class DivideByZeroException : public std::runtime_error
{
public:
	DivideByZeroException() : std::runtime_error("Program attempted to divide by zero"){}
	~DivideByZeroException(){ cout << "~DivideByZeroException().\n"; }
};


double Quotient(int numerator, int denominator)
{
	if (denominator == 0)
		throw DivideByZeroException();	//This is throw point. Function will terminate here.

	return ((double)numerator) / denominator;
}

void main()
{
	int n1;
	int n2;

	cout << "Enter two integers:\t";
	cin >> n1 >> n2;

	try
	{
		//try block contains code that might throw exception

		double result = Quotient(n1, n2);
		cout << "The quotient is:\t" << result << endl;
	}
	catch (DivideByZeroException &ex)
	{
		cout << "Exception occured: " << ex.what() << endl;
	}
	cout << "Last line of main.\n";
}