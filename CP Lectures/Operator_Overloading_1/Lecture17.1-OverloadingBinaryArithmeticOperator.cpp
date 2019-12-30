#include<iostream>
using namespace std;

class ComplexNumber
{
private:
	int real;
	int imaginary;
public:
	ComplexNumber();
	ComplexNumber(int, int);
	void Print();
	ComplexNumber operator+(const ComplexNumber&);
};

ComplexNumber::ComplexNumber()
{
	real = imaginary = 0;
}
ComplexNumber::ComplexNumber( int r, int i)
{
	real = r;
	imaginary = i;
}
void ComplexNumber::Print()
{
	cout << real;
	if (imaginary >= 0)
		cout << "+";
	cout << imaginary <<"i";
}
ComplexNumber ComplexNumber::operator+(const ComplexNumber& rhs)
{
	// Uncomment following lines of code to check associativity
	// remove the keyword const from prototype in order to run these lines.
	//Print();
	//cout << "+";
	//rhs.Print();	
	//cout << endl;

	ComplexNumber result;
	result.real = real + rhs.real;
	result.imaginary = imaginary + rhs.imaginary;
	
	return result;
}
void main()
{
	ComplexNumber c1(3,4);
	ComplexNumber c2(2, 2);
	ComplexNumber c3(3, 1);

	ComplexNumber c4 = c1 + c2 + c3;	//This is cascaded statement
	cout << "c4 = ";
	c4.Print();
	cout << endl;

}