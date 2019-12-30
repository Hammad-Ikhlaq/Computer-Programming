#include<iostream>
using namespace std;
void main()
{
	int i = 0, j = 0, total = 4;
	char **strArr = new char *[total];
	int size = 7;
	for (i = 0; i<total; ++i)
	{
		strArr[i] = new char[size - i];
		strArr[i][size - i - 1] = '\0';
	}
	for (i = 0; i<total; ++i)
	{
		for (j = 0; j<size - i - 1; ++j)
		{
			strArr[i][j] = 'A' + j;
		}
	}
	for (i = 0; i<total; ++i)
		cout << strArr[i] << endl;
	for (i = 0; i<total; ++i)
		cout << (strArr[i] + 1) << endl;
	cout << *strArr << endl;
	cout << **strArr << endl;
	cout << strArr[3] << endl;
	cout << strArr[2] + 1 << endl;
	cout << *strArr[3] + 2 << endl;
	cout << *(*strArr + 2) + 1 << endl;
	//cout << (strArr + 2)[3] << endl;
	system("pause");
}
