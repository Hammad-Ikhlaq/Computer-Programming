#include<iostream>
using namespace std;
int main()
{
	double*pt;
	double a[3] = { 1.2, 2.3, 3.4 };
	pt = &a[1];
	pt += 1;
	cout << *pt << endl;
	system("pause");
	return 0;
}