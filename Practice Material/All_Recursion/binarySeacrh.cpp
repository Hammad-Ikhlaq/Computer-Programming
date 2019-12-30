//# include <iostream>
//using namespace std;
//int binarySearch(int Array[], int start, int end, int size, int searchElement)
//{
//	int mid;
//	mid = (start + end) / 2;
//	if (start >= size || end < 0 && Array[mid] != searchElement)
//	{
//		return -1;
//	}
//	if (Array[mid] == searchElement)
//	{
//		return mid;
//	}
//	else if (Array[mid] < searchElement)
//	{
//		binarySearch(Array,mid+1,end, size , searchElement);
//	}
//	else if (Array[mid] > searchElement)
//	{
//		binarySearch(Array, start, end - 1, size, searchElement);
//	}
//}
//int main()
//{
//	int Array[] = { 1,2,3,4,5,6,7,8,9,10 };
//	int size = sizeof(Array) / sizeof(Array[0]);
//	int searchElement = 5;
//	cout << binarySearch(Array, 0, size - 1, size, searchElement);
//	system("pause");
//}