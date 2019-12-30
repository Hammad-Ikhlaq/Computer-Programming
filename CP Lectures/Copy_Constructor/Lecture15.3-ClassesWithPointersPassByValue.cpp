#include<iostream>
using namespace std;

class Rectangle{
private:
	int* lenght;
	int* width;
public:
	Rectangle();
	Rectangle(int, int);
	Rectangle(const Rectangle&);
	~Rectangle();
	void Print();
	const Rectangle& operator=(const Rectangle&);	
	void SetValues(int, int);
	bool IsEqual(Rectangle);
};
Rectangle::Rectangle()
{
	cout << "Default Constructor Called.\n\n";
	lenght = new int(0);
	width = new int(0);
}
Rectangle::Rectangle(int l, int w)
{
	cout << "Overloaded Constructor Called for "<<l<<" X "<<w<<".\n\n";
	lenght = new int(l);
	width = new int (w);
}
Rectangle::Rectangle(const Rectangle& rhs)
{
	cout<<"Copy Constructor Called to create a copy of Rectangle "<<*rhs.lenght<<" X "<<*rhs.width<<endl;
	lenght = new int( *rhs.lenght);
	width = new int ( *rhs.width);
}
Rectangle::~Rectangle()
{
	cout << "Destructor Called for rectangle "<<*lenght<<" X "<<*width<<"\n\n";
	delete lenght;
	delete width;
}
const Rectangle& Rectangle::operator=(const Rectangle& rhs)
{
	cout<<"Overloaded Assignment Operator Called for RHS "<<*rhs.lenght<<" X "<<*rhs.width<<endl;

	if( &rhs != this )	//Avoid self-assignment
	{
		//De-allocate previous memory and allocate new memory IF REQUIRED
		*lenght = *rhs.lenght;
		*width = *rhs.width;
	}
	return *this;
}

void Rectangle::Print()
{
	cout << *lenght << " X " << *width<<endl<<endl;
}
void Rectangle::SetValues(int l , int w)
{
	*lenght = l;
	*width = w;
}
bool Rectangle::IsEqual(Rectangle rhs)
{
	int areaLhs = *lenght**width;
	int areaRhs = *rhs.width * *rhs.lenght;

	if(areaLhs == areaRhs)
	{
		cout<<"Both Rectangles are Equal.\n";		
		return true;
	}
	else
	{
		cout<<"Both Rectangles are NOT Equal.\n";
		return false;
	}
}
void main()
{
	{
		Rectangle r1(2, 3);
		Rectangle r3(4, 5);

		cout << "\n\n\nGoing to pass an object by value to IsEqual function.\n\n";
		r1.IsEqual(r3);

		cout << "\n\n\nBack From IsEqual Function.\n";
				
		cout << "r3:\t";
		r3.Print();
		cout << "\n\n\nMain() is terminating. Everything will be destroyed now...\n\n\n";
		//Comment Copy Constructor and check what Complier's Copy Constructor does?
	}
	cout << "Press any key to continue...";
	getchar();
}