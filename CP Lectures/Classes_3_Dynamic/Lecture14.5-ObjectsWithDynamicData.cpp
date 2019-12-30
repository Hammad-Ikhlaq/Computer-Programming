#include<iostream>
using namespace std;

class Rectangle{
private:
	int* lenght;
	int* width;
public:
	Rectangle();
	Rectangle(int, int);
	~Rectangle();
	void SetValues(int, int);
	void Print();
};
Rectangle::Rectangle()
{
	cout << "Default Constructor Called.\n\n";
	lenght = new int;
	width = new int;
	*lenght = *width = 0;	
}
Rectangle::Rectangle(int l, int w)
{
	cout << "Overloaded Constructor Called with l = "<<l<<" and w = "<<w<<".\n\n";
	lenght = new int(l);
	width = new int(w);
}
Rectangle::~Rectangle()
{
	cout << "Destructor Called for rectangle "<<*lenght<<"X"<<*width<<"\n";
	delete lenght;//Deallocated memory from heap
	delete width;
}
void Rectangle::Print()
{
	//What will following line print now?
	//cout << "Rectangle is " << lenght << "X" << width<<endl<<endl;
	cout << "Rectangle is " << *lenght << "X" << *width << endl << endl;
}
void Rectangle::SetValues(int l, int w)
{
	*lenght = l;
	*width = w;
}
void main()
{
	//Create an object on stack
	Rectangle r1;
	r1.Print();
	r1.SetValues(3, 4);
	r1.Print();

	Rectangle r2;
}