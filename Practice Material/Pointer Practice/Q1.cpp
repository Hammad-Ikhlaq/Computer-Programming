#include<iostream>
using namespace std;
int*makeIntArray(int n)
{
	if (n == 0)
	{
		return nullptr;
	}
	return new int[n];
}
int*extendByFactor2(int*arr1, int n)
{
	int*arr2 = makeIntArray(2 * n);
	for (int i = 0; i < n; i++)
	{
		arr2[i] = arr1[i];
	}
	delete[]arr1;
	return arr2;
}
int*takeInput(int&n)
{
	int*arr = new int[n];
	int num = 1;
	int i = 0;
	cout << "Enter the array\n";
	while (num != -1)
	{
		while (num != -1 && i < n)
		{
			cin >> num;
			arr[i] = num;
			i++;
		}
		arr = extendByFactor2(arr, n);
		n = 2 * n;
	}
	return arr;
}
int main()
{
	int*ptr = nullptr;
	int n=10;
	ptr = takeInput(n);
	for (int i = 0; ptr[i]!=1; i++)
	{
		cout << ptr[i];
	}
	delete[]ptr;
	system("pause");
	return 0;
}