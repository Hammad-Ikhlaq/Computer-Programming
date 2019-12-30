#include<iostream>
using namespace std;

class Rectangle
{
private:
	int lenght;
	int width;

public:
	Rectangle();
	Rectangle(int, int);	//This is overloaded constructor (with parameters). Note the name and return type of constructor
	void Print();
	int Area();
	void SetLenght(int);
	void SetWidth(int);
	int GetLenght();
	int GetWidth();
	~Rectangle();
};

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
	cout << "\n\n\nDefault Constructor Called\n\n\n";
	lenght = width = 0;
}

Rectangle::~Rectangle()
{
	cout << "\n\n\nDestructor Called.\n\n\n";
}

Rectangle::Rectangle(int l, int w)
{
	cout << "\n\n\nOverloaded Constructor Called with parameters " << l << " and " << w << "\n\n\n";
	lenght = l;
	width = w;
}

void Rectangle::Print()
{
	cout << "\n\n\nPrinting Rectangle\n";
	cout << "Lenght = \t" << lenght << endl;
	cout << "Width = \t" << width << endl << endl << endl;
}

void main()
{

	cout << "Execution started in main()\n\n\n";

	cout << "Going to create r1\n\n";
	Rectangle r1;
	cout << "Rectangle 1:\n";
	r1.Print();

	cout << "Going to create r2\n\n";
	Rectangle r2(5, 10);
	cout << "Rectangle 2:\n";
	r2.Print();

	cout << "Area of Rectangle 1:\t" << r1.Area() << endl << endl;

	cout << "Area of Rectangle 2:\t" << r2.Area() << endl << endl;

	r1.SetLenght(2);
	r1.SetWidth(3);

	cout << "Print Updated Rectangle 1:\n";
	r1.Print();

	cout << "Reading Rectangle 2's data here:\n";
	cout << r2.GetLenght() << "\t" << r2.GetWidth() << endl << endl;

	cout << "main() is exiting....All the objects on stack are going to be destroyed.\n\n\n";


}