#include<iostream>
using namespace std;

class ComplexNumber
{
	friend ostream& operator<<(ostream&, const ComplexNumber&);// overloaded stream insertion operator
	friend istream& operator>>(istream&, ComplexNumber&);// overloaded stream insertion operator
private:
	int real;
	int imaginary;
public:
	ComplexNumber();
	ComplexNumber(int, int);
	void Print();
	ComplexNumber operator+(const ComplexNumber&);
	ComplexNumber& operator++();// PreIncrement
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
//Overloaded PreIncrement
ComplexNumber& ComplexNumber::operator++()
{	
	real++;
	return *this;
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
//overloaded stream insertion operator
ostream& operator<<(ostream& out, const ComplexNumber& obj)
{
	out << obj.real;
	if (obj.imaginary >= 0)
		out << "+";
	out << obj.imaginary << "i";
	return out;	// to enable cascading
}

//overloaded stream extraction operator
istream& operator>>(istream& in, ComplexNumber& obj)
{
	in >> obj.real;
	in >> obj.imaginary;
	return in;	// to enable cascading
}
void main()
{
	ComplexNumber c1(3,4);
	ComplexNumber c2(2, 2);
	ComplexNumber c3(3, 1);

	cout << "c1 = " << c1 << endl;

	int i = 10;

	cout << "++i = " << ++i << endl;
	cout << "i = " << i << endl;

	cout << "++c1 = " << ++c1 << endl;
	cout << "c1 = " << c1 << endl;

	ComplexNumber c4 = ++c2 + c3;

	cout << "c4 = " << c4 << endl;
}