#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
using namespace std;
void RemoveFromMatrix(char**Matrix1, const char rchar, char**Matrix2, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (Matrix1[i][j]==rchar)
			{
				for (int y = 0; y < rows; y++)
				{
					for (int z = 0; z < cols; z++)
					{
						if (y==i||z==j)
						{
							Matrix2[y][z] = '-';
						}
						else
						{
							Matrix2[y][z] = Matrix2[y][z];
						}
					}
				}
			}
		}
	}
}
int main()
{
	int rows = 4;
	int cols = 7;
	char**Matrix = new char*[rows];
	char**temp1 = new char*[rows];
	char**temp2 = new char*[rows];
	for (int i = 0; i < cols; i++)
	{
		Matrix[i] = new char[cols];
		temp1[i] = new char[cols];
		temp2[i] = new char[cols];
	}
	Matrix[0] = "bcdefh";
	strcpy(temp1[0], Matrix[0]);
	Matrix[1] = "tuxagh";
	strcpy(temp1[1], Matrix[1]);
	Matrix[2] = "yilmna";
	strcpy(temp1[2], Matrix[2]);
	Matrix[3] = "stuvwx";
	strcpy(temp1[3], Matrix[3]);
	for (int i = 0; i < rows; i++)
	{
		cout << Matrix[i] << endl;
	}
	cout << endl;
	RemoveFromMatrix(Matrix, 'a', temp1, rows, cols);
	int a = 0;
	int b = 0;
	for (int i = 0; i < rows; i++)
	{
		b = 0;
		for (int j = 0; j < cols; j++)
		{
			if (temp1[i][j]!='-')
			{
				temp2[a][b] = temp1[i][j];
				b++;
			}
		}
		a++;
	}
	for (int i = 0; i < rows; i++)
	{
		cout << temp2[i] << endl;
	}
	system("pause");
	return 0;
}
