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
	bool operator==(const ComplexNumber&);
};

ComplexNumber::ComplexNumber()
{
	real = imaginary = 0;
}
ComplexNumber::ComplexNumber(int r, int i)
{
	real = r;
	imaginary = i;
}
void ComplexNumber::Print()
{
	cout << real;
	if (imaginary >= 0)
		cout << "+";
	cout << imaginary << "i";
}
bool ComplexNumber::operator==(const ComplexNumber& rhs)
{
	if (real == rhs.real && imaginary == rhs.imaginary)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void main()
{
	ComplexNumber c1(2,4);
	ComplexNumber c2(2, 4);
	ComplexNumber c3(4, 2);
	if (c1 == c2)
		cout << "c1 is Equal to c2" << endl;
	else
		cout << "c1 is NOT Equal to c2" << endl;

	if (c1 == c3)
		cout << "c1 is Equal to c3" << endl;
	else
		cout << "c1 is NOT Equal to c3" << endl;


}