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
int*Shrinkby1(int*arr1, int&n)
{
	int*arr2 = makeIntArray(n - 1);
	for (int i = 0; i < n-1; i++)
	{
		arr2[i] = arr1[i];
	}
	delete[]arr1;
	n = n--;
	return arr2;
}
int*extendBy1(int*arr1, int&n)
{
	int*arr2 = makeIntArray(n + 1);
	for (int i = 0; i < n; i++)
	{
		arr2[i] = arr1[i];
	}
	n++;
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
		while (num != -1)
		{
			cin >> num;
			arr[i] = num;
			i++;
			arr = extendBy1(arr, n);
		}
	}
	return arr;
}
int main()
{
	int*ptr = nullptr;
	int n = 1;
    ptr = takeInput(n);
	for (int i = 0; ptr[i] != -1; i++)
	{
		if (ptr[i]==ptr[i+1])
		{
			for (int j = i + 1; ptr[j] != -1; j++)
			{
				ptr[j] = ptr[j + 1];
			}
			i--;
			ptr = Shrinkby1(ptr, n);
		}
	}
	ptr = Shrinkby1(ptr, n);
	ptr = Shrinkby1(ptr, n);
	for (int i = 0; i<n; i++)
	{
		cout << ptr[i];
	}
	system("pause");
	return 0;
}