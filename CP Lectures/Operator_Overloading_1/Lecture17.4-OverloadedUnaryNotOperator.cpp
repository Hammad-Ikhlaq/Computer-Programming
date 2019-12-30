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
	bool operator!();
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
bool ComplexNumber::operator!()
{
	if (real == 0 && imaginary == 0)
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
	ComplexNumber c1;
	if (!c1)
		cout << "c1 is zero" << endl;
	else
		cout << "c1 is not zero" << endl;
	

}