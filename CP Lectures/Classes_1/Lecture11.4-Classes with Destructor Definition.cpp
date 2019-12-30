#include<iostream>
using namespace std;

class Rectangle
{
private:
	int lenght;
	int width;

public:
	Rectangle();
	void Print();
	~Rectangle();	//Class can have only one destructor, without any parameters. Note the name and return type of destructor
};


Rectangle::Rectangle()
{
	cout << "\n\n\nDefault Constructor Called\n\n\n";
	lenght = width = 0;
}

Rectangle::~Rectangle()
{
	cout << "\n\n\nDestructor Called.\n\n\n";	
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

	Rectangle r1;
	r1.Print();

	cout << "main() is exiting....All the objects on stack are going to be destroyed.\n\n\n";
}