#include<iostream>
using namespace std;

class Rectangle{
private:
	int lenght;
	int width;
public:
	Rectangle();
	Rectangle(int, int);
	~Rectangle();
	void SetValues(int, int);
	void Print();
};
Rectangle::Rectangle()
{
	lenght = width = 0;
	cout << "Default Constructor Called.\n\n";
}
Rectangle::Rectangle(int l, int w)
{
	cout << "Overloaded Constructor Called with l = " << l << " and w = " << w << ".\n\n";
	lenght = l;
	width = w;
}
Rectangle::~Rectangle()
{
	cout << "Destructor Called for rectangle " << lenght << "X" << width << "\n";
}
void Rectangle::Print()
{
	cout << "Rectangle is " << lenght << "X" << width << endl << endl;
}
void Rectangle::SetValues(int l, int w)
{
	lenght = l;
	width = w;
}
void main()
{
	Rectangle r1;
	Rectangle r2(2, 3);
}