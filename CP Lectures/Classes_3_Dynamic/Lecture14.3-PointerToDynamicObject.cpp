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
	cout << "Overloaded Constructor Called with l = "<<l<<" and w = "<<w<<".\n\n";
	lenght = l;
	width = w;
}
Rectangle::~Rectangle()
{
	cout << "Destructor Called for rectangle "<<lenght<<"X"<<width<<"\n";
}
void Rectangle::Print()
{
	cout << "Rectangle is " << lenght << "X" << width<<endl<<endl;
}
void Rectangle::SetValues(int l, int w)
{
	lenght = l;
	width = w;
}
void main()
{
	Rectangle *rectPtr1;
	Rectangle r1(3,4);

	rectPtr1 = &r1; //rectPtr is pointing to r1
	cout << "Print Rectangle 1:\n";
	rectPtr1->Print();
	cout << "rectPtr1 = " << rectPtr1 << endl;
	
	Rectangle *rectPtr2 = new Rectangle;	//rectPtr2 pointing to an object on heap
	cout << "Print Rectangle 2:\n";
	rectPtr2->Print();
	rectPtr2->SetValues(5, 10);
	rectPtr2->Print();

	Rectangle *rectPtr3 = new Rectangle(100, 200);
	cout << "Print Rectangle 3:\n";
	rectPtr3->Print();
	

	cout << "Function is terminating. Everything will be disposed now...\n\n";
	//Comment both of the lines below and see what happens
	delete rectPtr2;
	delete rectPtr3;
}