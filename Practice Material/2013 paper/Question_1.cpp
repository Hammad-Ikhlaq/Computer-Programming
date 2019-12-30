# include <iostream>
using namespace std;
class Array 
{
	// Given In Question...
	int * a;//dynamic array
	int capacity;//capacity (total space in the array)
	int size;  //size (number of elements inserted)
	

	// self created Members
	int *temp1;

public:

	Array()
	{
		capacity = 0;
		size = 0;
		a = new int[capacity];
	}

	Array(int *temp , int n , int cap)
	{
		size = n;
		if (cap <= 0 || cap < n)
		{
			capacity = size;
		}
		else
		{
			capacity = cap;
		}
		a = new int[capacity];
		for (int i = 0; i < size; i++)
		{
			a[i] = temp[i];
		}
	}

	void insert(int x)
	{
		if (size == capacity)
		{
			expandCapacity();
		}
		a[size] = x;
		size++;
	}


	// Helping fucntion Not Asked In Question.....
	void expandCapacity()
	{
		if (capacity == 0)
		{
			capacity = 1;
			a = new int[1];
		}
		else
		{
			temp1 = new int[capacity];
			for (int i = 0; i < capacity; i++)
			{
				temp1[i] = a[i];
			}
			delete[]a;
			a = new int[capacity * 2];
			for (int i = 0; i < capacity; i++)
			{
				a[i] = temp1[i];
			}
			capacity = capacity * 2;
			delete[]temp1;
		}
	}

	void reverseInRange(int start , int end)
	{
		int count1 = 0;
		int count2 = size - 1;
		int save;
		while (count1 < count2)
		{
			if (a[count1] >= start && a[count1] <= end && a[count2] >= start && a[count2])
			{
				// swapping.....
				save = a[count1];
				a[count1] = a[count2];
				a[count2] = save;
				count2--;
			}
			count1++;
		}
	}

	// Helping fucntion for Verification Not Asked In Question.....
	void display()
	{
		for (int i = 0; i < size; i++)
		{
			cout << a[i] << "\t";
		}
	}
};

int main()
{
	int temp[] = { 12,4,6,11,5 };
	Array A; 	// make an empty array of capacity 0

	Array B(temp, 5, 10);
	/*
	Make an array with size 5 and capacity 10. If no capacity is specified or capacity
	is less than size, then set capacity equal to size, and allocate the array of
	that capacity.  */

	int n, input;
	cout << "Enter How Many Number You Want to enter\n\n";
	cin >> n;
	cout << "Enter : " << n << " Elements\n\n";
	for (int i = 0; i < n; i++)
	{
		cin >> input;
		B.insert(input);
		// B.insert(input);// try this one also
		/*
		Insert puts the new integer at the next available index
		in the array. If size exceeds capacity then, a new array
		of double capacity is allocated, data is copied into it
		and the older array is de-allocated. 	*/
	}


	// for verification......Not Asked In Question...
	B.display();
	// B.display(); // try this one also

	cout << "\n\n After Reversing\n\n";
	B.reverseInRange(3, 7);
	B.display();
	// B.reverseInRange(3,7); // try this one also
	/*
	The order of all elements in the given range is reversed,
	keeping the remaining Elements un-disturbed.
	For example, if the array contained 2,6,8,4,1,13,7,5,
	then after this call it will become: 2,5,8,7,1,13,4,6
	(notice the elements in bold have been reversed) 	*/
	system("pause");
}