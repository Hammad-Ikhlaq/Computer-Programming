#include<iostream>
using namespace std;
void printArray(int *arr, int size)
{
	for (int i = 0; i<size; ++i)
		cout << arr[i] << ' ';
	cout << endl;
}
int main()
{
	int localArray[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int *arr;
	arr = localArray + 3;
	printArray(arr, 4);
	*arr = 15;
	arr[-2] = 7;
	printArray(localArray, 10);
	unsigned char x = 0x01, y = 0xff;
	unsigned char a = 203;
	x = x << 2;
	cout << (int)x << endl;
	x = a & y;
	cout << (int)x << endl;
	system("pause");
	return 0;
}