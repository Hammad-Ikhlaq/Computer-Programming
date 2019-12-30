#include<iostream>
using namespace std;

void main()
{
	char* myString = new char[10];
	char* temp = myString;	//Where is temp pointing

	cout << "myString = " << myString << endl<<endl;	//Junk Value saved in char array right now
	cout << "temp = " << temp << endl << endl;

	myString = "Test String";

	cout << "After modification:\n\nmyString = " << myString << endl << endl;

	cout << "temp = " << temp << endl << endl;	

	//myString has started pointing to string literal or string constant (a temp buffer on stack) that contains
	// "Test String" and temp is still pointing to memory allocated in heap.
	//If we want to write "Test String" in heap we will have to copy it in heap explicitly.

	cout << "Enter a String in Temp:\t";
	cin >> temp;

	cout << "After taking input from user:\n\nmyString = " << myString << endl << endl;

	cout << "temp = " << temp << endl << endl;
}