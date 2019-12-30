#include<iostream>
using namespace std;
void switchPtr(int *p, int *q)
{
	int *temp = p;
	p = q;
	q = temp;
}
int acceptPtr(int *p, int *q)
{
	*p = *q + 5;
	*q = *q + 10;
	p = q;
	*p = 5 + *q;
	*q = *p + 1;
	return *p +1;
}// both ptrs have same value so change one will effect others data
int dontComplicate(int *p, int *q, int &a, int &b)
{
	a = a + 1;
	b = b + 2;
	q = p;
	*p = 3;
	*q = 5;
	a = a + 4;
	b = b + 5;// it is old one baba
	return *p + *q;
}
int notVerySimple(int *ptr1, int *ptr2, int &a, int &b)
{
	*ptr1 = 1;
	*ptr2 = 5;
	a = 4;
	b = 3;
	return a + b;
}
int main(){
	int x = 1, y = 2, z = 0;
	int *ptr1 = &x;
	int *ptr2 = &y;
	//cout <<"Value of x is: "<< x << endl;
	//cout << "Value of y is: " << y << endl;
	//cout << "Value of z is: " << z << endl;
	//cout << "Value of ptr1 is: " << ptr1 << endl;
	//cout << "Value of *ptr1 is: " << *ptr1 << endl;
	//cout << "Value of ptr2 is: " << ptr2 << endl;
	//cout << "Value of *ptr2 is: " << *ptr2 << endl;
	switchPtr(ptr1, ptr2);//nothing will happen
	//cout << "Value of x is: " << x << endl;
	//cout << "Value of y is: " << y << endl;
	//cout << "Value of z is: " << z << endl;
	//cout << "Value of ptr1 is: " << ptr1 << endl;
	//cout << "Value of *ptr1 is: " << *ptr1 << endl;
	//cout << "Value of ptr2 is: " << ptr2 << endl;
	//cout << "Value of *ptr2 is: " << *ptr2 << endl;
	z = acceptPtr(ptr1, ptr2);
	//cout << "Value of x is: " << x << endl;
	//cout << "Value of y is: " << y << endl;
	//cout << "Value of z is: " << z << endl;
	//cout << "Value of ptr1 is: " << ptr1 << endl;
	//cout << "Value of *ptr1 is: " << *ptr1 << endl;
	//cout << "Value of ptr2 is: " << ptr2 << endl;
	//cout << "Value of *ptr2 is: " << *ptr2 << endl;
	x = 0; y = 1;
	z = dontComplicate(ptr2, ptr1, y, x);
	//cout << "Value of x is: " << x << endl;
	//cout << "Value of y is: " << y << endl;
	//cout << "Value of z is: " << z << endl;
	//cout << "Value of ptr1 is: " << ptr1 << endl;
	//cout << "Value of *ptr1 is: " << *ptr1 << endl;
	//cout << "Value of ptr2 is: " << ptr2 << endl;
	//cout << "Value of *ptr2 is: " << *ptr2 << endl;
	z = notVerySimple(ptr1, ptr2, x, y);
	cout << "Value of x is: " << x << endl;
	cout << "Value of y is: " << y << endl;
	cout << "Value of z is: " << z << endl;
	cout << "Value of ptr1 is: " << ptr1 << endl;
	cout << "Value of *ptr1 is: " << *ptr1 << endl;
	cout << "Value of ptr2 is: " << ptr2 << endl;
	cout << "Value of *ptr2 is: " << *ptr2 << endl;
	system("pause");
	return 0;
}