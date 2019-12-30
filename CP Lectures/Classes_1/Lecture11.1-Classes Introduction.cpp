#include<iostream>
using namespace std;

class Rectangle
{		

 private:	//This is access specifier. All members which are private are not accessible beyond class scope (outside world)
	int lenght;		//Data Member
	int width;		//Data Member
	
};

void main()
{
	Rectangle r1;

	//UNCOMMENT THIS LINE FOR PRINTING

	//cout << r1;		//cout does not know how to display user defined data type Rectangle.
	// How can I print r1?
	
}