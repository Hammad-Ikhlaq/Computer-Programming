//#include <iostream>
//using namespace std;
//
//int sum_F(int A[][2], int sum, int row, int col, int counter1, int counter2)
//{
//	if (counter1 == row)
//	{
//		return sum;
//	}
//	else
//	{
//		sum = ((A[counter1][counter2] + A[counter1][counter2]) - A[counter1][counter2]) + sum;
//		counter2++;
//		if (counter2 == col)
//		{
//			counter2 = 0;
//			counter1++;
//		}
//		sum_F(A, sum, row, col, counter1, counter2);
//	}
//}
//int main()
//{
//	const int size = 2;
//	int A[][size] = { { 1,2 },{ 3,4 } };
//	cout << sum_F(A, 0, size, size, 0, 0);
//
//	system("pause");
//}