//#include <iostream>
//using namespace std;
//
//void sum(int A[][2] , int B[][2],int Sum[][2], int row , int col, int counter1 , int counter2)
//{
//	if (counter1 == row)
//	{
//		return;
//	}
//	else
//	{
//		Sum[counter1][counter2] = A[counter1][counter2] + B[counter1][counter2];
//		counter2++;
//		if (counter2 == col)
//		{
//			counter2 = 0;
//			counter1++;
//		}
//		sum(A, B, Sum, row, col, counter1, counter2);
//	}
//}
//int main()
//{
//	const int size = 2;
//	int A[][size] = { {1,2},{3,4} };
//	int B[][size] = { { 1,2 },{ 3,4 } };
//	int C[size][size];
//	sum(A, B, C, size, size, 0, 0);
//	for (int i = 0; i < size; i++)
//	{
//		for (int j = 0; j < size; j++)
//		{
//			cout << C[i][j] << "\t";
//		}
//		cout << "\n";
//	}
//	system("pause");
//}