#include<iostream>
using namespace std;

void main()
{
	bool test = true;
	cout << "!test:\t" << !test << endl; // Not of true = false = 0

	bool test1 = false;
	cout << "!test1:\t" << !test1 << endl; // Not of false = true

	int test2 = 1;
	cout << "!test2:\t" << !test2 << endl;	//if(test2 == 0)

	int test3 = 0;
	cout << "!test3:\t" << !test3 << endl;	//if(test3 == 0)

	int test4 = 10;
	cout << "!test4:\t" << !test4 << endl;	//if(test4 == 0)

	cout << "int(true):\t" << int(true) << endl;
	cout << "int(false):\t" << int(false) << endl;
}