#include<iostream>
using namespace std;
	int * square(int * a) 
	{
		int *s = new int;
		*s = *a * *a;
		return s;
	}
int main()
{
		int i = 10;
		int j = *square(&i);
		cout << j << endl;
	system("pause");
	return 0;
}