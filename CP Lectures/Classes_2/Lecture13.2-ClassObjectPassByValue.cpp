#include<iostream>
using namespace std;

class Rectangle
{
private:
	int lenght;
	int width;

public:
	Rectangle();
	Rectangle(int, int);
	void Print();
	int Area();
	void SetLenght(int);
	void SetWidth(int);
	void Input();
	int GetLenght();
	int GetWidth();
	int Compare(Rectangle);
	~Rectangle();
};

int Rectangle::Compare(Rectangle rhs)
{
	int areaLhs = Area();	//Area of the object for which the function has been called (Left hand side object)
	int areaRhs = rhs.Area();	//Area of the object which has been passed as parameter (Right hand side object)

	//Check addresses
	cout <<"&rhs:\t" <<&rhs << endl;
	cout << "&areaLhs:\t" << &areaLhs << endl;
	cout << "&areaRhs:\t" << &areaRhs << endl;

	//changing parameter here
	rhs.lenght = rhs.lenght * 100;
	if (areaLhs < areaRhs)
	{
		cout << "Left Hand Side Rectangle is Smaller than RHS Rectangle.\n";
		return -1;
	}
	else if (areaLhs > areaRhs)
	{
		cout << "Left Hand Side Rectangle is Larger than RHS Rectangle.\n";
		return 1;
	}
	else
	{
		cout << "Left Hand Side Rectangle is Equal to RHS Rectangle.\n";
		return 0;
	}
}

void Rectangle::Input()
{
	cout << "Enter Lenght:\t";
	cin >> lenght;
	cout << "Enter Width:\t";
	cin >> width;
}

int Rectangle::GetLenght()
{
	return lenght;
}

int Rectangle::GetWidth()
{
	return width;
}

void Rectangle::SetLenght(int l)
{
	lenght = l;
}

void Rectangle::SetWidth(int w)
{
	width = w;
}

int Rectangle::Area()
{
	return lenght*width;
}

Rectangle::Rectangle()
{
	lenght = width = 0;
}

Rectangle::~Rectangle()
{	
}

Rectangle::Rectangle(int l, int w)
{
	lenght = l;
	width = w;
}

void Rectangle::Print()
{	
	cout << lenght << "X" << width << endl;
}

void main()
{

	cout << "Going to create r1\n\n";
	Rectangle r1;

	cout << "Input r1:\n";
	r1.Input();

	cout << "Going to create r2\n\n";
	Rectangle r2(5, 10);
	
	cout << "Rectangle 1:\n";
	r1.Print();

	
	cout << "Rectangle 2:\n";
	r2.Print();

	cout << "Address of r1:\t" << &r1 << endl;
	cout << "Address of r2:\t" << &r2 << endl;

	cout << "r1.Compare(r2)\n\n";
	r1.Compare(r2);	

	//Check if r2 changed in Compare function
	cout << "Rectangle 2 after function call:\n";
	r2.Print();

}