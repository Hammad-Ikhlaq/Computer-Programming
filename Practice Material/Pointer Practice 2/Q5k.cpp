#include<iostream>
using namespace std;
int main()
{
	int a = 5;
	int * ptr = new int;
	ptr[0] = a;
	cout << ptr[0] << endl;
	ptr = &a;
	system("pause");
	return 0;
}