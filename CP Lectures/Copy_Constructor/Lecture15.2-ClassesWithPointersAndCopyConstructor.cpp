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
	cout<<"Overloaded Assignment Operator Called for LHS "<<*rhs.lenght<<" X "<<*rhs.width<<endl;

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
void main()
{
	{
		Rectangle r1(2, 3);

		{
			Rectangle r2 = r1;	//Will this call assignment operator or copy constructor?
			cout << "r2:\t";
			r2.Print();
		}
		cout << "r1:\t";
		r1.Print();		
		cout << "\n\n\nMain() is terminating. Everything will be destroyed now...\n\n\n";
		//Comment the Copy Constructor and see what built-in copy constructor does.
	}

	cout << "Press any key to continue...";
	getchar();
}