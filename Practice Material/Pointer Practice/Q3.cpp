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
int*extendBy1(int*arr1, int n)
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
int*takeInput(int & n)
{
	n = 0;
	int*arr = new int[1];
	int num = 1;
	while (num>0)
	{
		cin >> num;
		if (num == 0)
		{
			break;
		}
		else
		{
			arr[n] = num;
			arr = extendBy1(arr, n+1 );
			n++;
		}
	}
	return arr;
}
int * merging(int * ptr1, int size1, int * ptr2, int size2)
{
	int i = 0, j = 0,k=0;
	int * merged = new int[size1 + size2];
	while (k<=size1+size2)
	{
		if (ptr1[i]<=ptr2[j]&&i<size1)
		{
			merged[k] = ptr1[i];
			k++;
			i++;
		}
		else
		{
			merged[k] = ptr2[j];
			k++;
			j++;
		}
	}
	return merged;
}
int main()
{
	int*ptr1 = nullptr;
	int*ptr2 = nullptr;
	int*ptr3 = nullptr;
	int n1 = 0;
	int n2 = 0;
	cout << "Enter the first sorted array\n";
	ptr1 = takeInput(n1);
	cout << "Enter the second sorted array\n";
	ptr2 = takeInput(n2);
	ptr3 = merging(ptr1, n1, ptr2, n2);
	for (int i = 0; i< n1 + n2; i++)
	{
		cout << ptr3[i] << " ";
	}
	delete[]ptr1;
	delete[]ptr2;
	system("pause");
	return 0;
}