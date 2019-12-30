//# include <iostream>s
//using namespace std;
//void bubbleSort(int A[], int size)
//{
//	if (size < 0)
//	{
//		return;
//	}
//	int temp;
//	for (int j = 0; j < size; j++)
//	{
//		if (A[j] > A[j + 1])
//		{
//			temp = A[j + 1];
//			A[j + 1] = A[j];
//			A[j] = temp;
//		}
//	}
//	size--;
//	bubbleSort(A, size);
//}
//int main()
//{
//	int A[] = {10,9,8,7,6,5,4,3,2,1};
//	int size = 10;
//	int temp;
//	bubbleSort(A, size - 1);
//	for (int i = 0; i < size; i++)
//	{
//		cout << A[i] <<endl;
//	}
//	system("pause");
//}