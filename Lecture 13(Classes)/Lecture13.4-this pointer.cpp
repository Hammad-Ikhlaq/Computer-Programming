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
	Rectangle GetRotatedRectangle();
	~Rectangle();
	void TestThisPointer();
};

Rectangle Rectangle::GetRotatedRectangle()
{
	Rectangle temp;
	temp.lenght = width;
	temp.width = lenght;
	return temp;
}

int Rectangle::Compare(Rectangle rhs)
{
	int areaLhs = Area();
	int areaRhs = rhs.Area();

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
	cout << "\n\n\nPrinting Rectangle\n";
	cout << "Lenght = \t" << lenght << endl;
	cout << "Width = \t" << width << endl << endl << endl;
}

void Rectangle::TestThisPointer()
{
	cout << "this:\t" << this << endl;
	cout << "Rectangle:\t" << this->lenght << "X" << this->width << endl;
	cout << "Rectangle:\t" << (*this).lenght << "X" << (*this).width << endl;
	cout << "Area:\t" << this->Area()<<endl<<endl;
}

void main()
{	
	Rectangle r1(5, 10);
	cout << "Rectangle 1:\n";
	r1.Print();
	cout << "Address of r1:\t" << &r1 << endl;
	cout << "Testing This for r1:\n\n";
	r1.TestThisPointer();


	Rectangle r2;
	cout << "Rectangle 2:\n";
	r2.Print();	
	cout << "Address of r2:\t" << &r2 << endl;
	cout << "Testing This for r2:\n\n";
	r2.TestThisPointer();



}