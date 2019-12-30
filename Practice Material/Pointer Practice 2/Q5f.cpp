#include<iostream>
using namespace std;
int * cube(int * a) {
	int s = *a**a**a;
	return &s;
}
int main()
{
	int i = 10;
	int j = *cube(&i);
	cout << j << endl;
	system("pause");
	return 0;
}