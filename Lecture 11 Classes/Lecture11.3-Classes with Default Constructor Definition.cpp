#include<iostream>
using namespace std;

class Rectangle
{
private:
	int lenght;
	int width;

public:
	Rectangle();	//This is default constructor (without any parameters). Note the name and return type of constructor
	void Print();
};

//Here is the definition of the Default Constructor
Rectangle::Rectangle()
{
	cout << "\n\n\nDefault Constructor Called\n\n\n";
	lenght = width = 0;
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

}