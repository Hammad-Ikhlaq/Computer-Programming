//# include <iostream>
//using namespace std;
//void insertionSort(int Array[], int size, int counter)
//{
//	int temp;
//	if (counter == size)
//	{
//		return;
//	}
//	for (int j = counter; j > 0; j--)
//	{
//		if (Array[j] < Array[j - 1])
//		{
//			temp = Array[j];
//			Array[j] = Array[j - 1];
//			Array[j - 1] = temp;
//		}
//	}
//	counter++;
//	insertionSort(Array , size , counter);
//	
//}
//int main()
//{
//	int temp;
//	int Array[] = {10,9,8,7,6,5,4,3,2,1};
//	insertionSort(Array , 10 , 0);
//	for (int i = 0; i < 10; i++)
//	{
//		cout << Array[i] << endl << endl;
//	}
//	system("pause");
//}