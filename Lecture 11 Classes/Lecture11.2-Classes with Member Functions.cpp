#include<iostream>
using namespace std;

class Rectangle
{
private:
	int lenght;
	int width;

public:
	void Print();		//Member Function
};

void Rectangle::Print()
{
	//This function displays the state(information) of an object
	cout << "\n\n\nPrinting Rectangle\n";
	cout << "Lenght = \t" << lenght << endl;
	cout << "Width = \t" << width << endl<<endl<<endl;
}

void main()
{
	Rectangle r1;
	r1.Print();		// Dot is "member access operator" to access a data/function member of an object
	//This is printing junk state of the object
	//How can we make the state of object deterministic?

}