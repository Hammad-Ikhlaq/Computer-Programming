#include<iostream>
using namespace std;
int main() 
{
	char *a[] = { "Argentina", "Korea", "Greece", "Nigeria" };
	cout << *(a + 1) << endl;
	cout << *a[0] << endl;
	cout << a[3] << endl;
	cout << a[3][1] << endl;
	system("pause");
	return 0;
}