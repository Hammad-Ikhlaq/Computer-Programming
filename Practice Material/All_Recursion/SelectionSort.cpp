//# include <iostream>
//using namespace std;
//void selectionSort(int Array[], int size, int counter)
//{
//	int temp = 0;
//	int max = 0;
//	int index = 0;
//	if (counter == size)
//	{
//		return;
//	}
//	max = Array[counter];
//	index = counter;
//	for (int j = counter; j < size; j++)
//	{
//		if (max > Array[j])
//		{
//			max = Array[j];
//			index = j;
//		}
//	}
//	temp = Array[counter];
//	Array[counter] = Array[index];
//	Array[index] = temp;
//	counter++;
//	selectionSort(Array, size, counter);
//}
//
//int main()
//{
//	int Array[] = { 10,9,8,7,6,5,4,3,2,1 };
//	selectionSort(Array, 10, 0);
//	for (int i = 0; i < 10; i++)
//	{
//		cout << Array[i] << endl << endl;
//	}
//	system("pause");
//}