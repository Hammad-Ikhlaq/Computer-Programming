#include<iostream>
using namespace std;
int * product(int a, int b)
{
	int mul = a*b;
	return &mul;
}
int main()
{
	int x = 7, y = 10;
	int * p = product(x, y);
	cout << *p;
	system("pause");
	return 0;
}