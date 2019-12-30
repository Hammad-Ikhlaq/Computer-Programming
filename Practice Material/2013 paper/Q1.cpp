#include<iostream>
using namespace std;
class Array{
	int * a;//dynamic array
	int cap;//capacity (total space in the array)
	int n;  //size (number of elements inserted)
public:
	Array(int*arr, int num, int c)
	{
		a = arr;
		if (c<num)
		{
			c = num;
		}
		a = new int[num];
		cap = c;
		n = num;
	}
	Array()
	{
		a = NULL;
		cap = 0;
		n = 0;
	}
	void insert(int digit)
	{
		if (n>=cap)
		{
			cap = 2 * cap;
			int*temp = new int[cap];
			delete[]a;
			a = NULL;
			a = temp;
		}
		a[n] = digit;
		n += 1;
	}
	void reverseInRange(int start, int end)
	{
		if (end < cap)
		{
			int mid = (start + end) / 2;
			for (int i = start; i < mid; i++)
			{
				swap(a[i], a[end - i]);
			}
		}
	}
};

int main()
{
	int temp[] = { 12, 4, 6, 11, 5 };
	Array A; 	// make an empty array of capacity 0

	Array B(temp, 5, 10);
	/*
	Make an array with size 5 and capacity 10. If no capacity is specified or capacity
	is less than size, then set capacity equal to size, and allocate the array of
	that capacity.  */

	int n, input;
	cin >> n;
	for (int i = 0; i<n; i++){
		cin >> input;
		A.insert(i);
		/*
		Insert puts the new integer at the next available index
		in the array. If size exceeds capacity then, a new array
		of double capacity is allocated, data is copied into it
		and the older array is de-allocated. 	*/
	}
	A.reverseInRange(3, 7);
	/*
	The order of all elements in the given range is reversed, keeping the remaining Elements
	un-disturbed. For example, if the array contained 2,6,8,4,1,13,7,5, then after this call it will become: 2,5,8,7,1,13,4,6 (notice the elements in bold have been reversed) 	*/

	return 0;
}
