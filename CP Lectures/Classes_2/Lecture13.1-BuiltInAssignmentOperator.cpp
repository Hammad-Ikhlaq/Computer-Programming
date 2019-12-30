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
	cout << "Default Constructor Called\n";
	lenght = width = 0;
}

Rectangle::~Rectangle()
{
	cout << "Destructor Called for " << lenght << "X" << width << endl;
}

Rectangle::Rectangle(int l, int w)
{
	cout << "Overloaded Constructor Called with parameters " << l << " and " << w << endl;
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

	cout << "Testing Built-in Assignment Operator: r1 = r2\n\n";
	r1 = r2;	//Built-in Assignment Operator

	cout << "Rectangle 1:\n";
	r1.Print();

	cout << "Rectangle 2:\n";
	r2.Print();


	cout << "main() is exiting....All the objects on stack are going to be destroyed.\n\n\n";


}