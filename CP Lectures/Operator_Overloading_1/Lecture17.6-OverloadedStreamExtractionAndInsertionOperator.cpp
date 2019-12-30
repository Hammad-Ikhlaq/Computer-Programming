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
	ComplexNumber c1, c2, c3;
	cout << "Enter c1, c2 and c3 (real and imaginary parts) one by one:\n";
	cin >> c1 >> c2 >> c3;
	cout << "c1 = " << c1 << "\nc2 = " << c2 << "\nc3 = " << c3 << endl;


}