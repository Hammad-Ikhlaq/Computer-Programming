# include <iostream>
using namespace std;

const int cols = 6;
const int rows1 = 4;
void RemoveFromMatrix(char Matrix1[][cols], const char rChar, char Matrix2[][cols], const int rows)
{
	// use for Storing index of  rows that contains rChar...
	int *tempRows = new int[rows];
	int tempRowsCount = 0;
	bool flag1;

	// use for Storing index of  cols that contains rChar....
	int *tempCols = new int[cols];
	int tempColsCount = 0;
	bool flag2;

	char matrixTemp[rows1][cols];
	// checking and storing indexes in Which rchar is Existing in Columns And Rows ...
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (Matrix1[i][j] == rChar)
			{
				tempRows[tempRowsCount] = i;
				tempCols[tempColsCount] = j;
				tempRowsCount++;
				tempColsCount++;
				break;
			}
		}
	}

	// checking and saving the elements of rows and cols in which there is no rChar....
	for (int i = 0; i < rows; i++)
	{
		flag1 = true;
		for (int k = 0; k < tempRowsCount; k++)
		{
			if (i == tempRows[k])
			{
				flag1 = false;
				break;
			}
		}
		for (int j = 0; j < cols; j++)
		{
			flag2 = true;
			for (int k = 0; k < tempColsCount; k++)
			{
				if (j == tempCols[k])
				{
					flag2 = false;
					break;
				}
			}
			if (flag1 == true && flag2 == true)
			{
				matrixTemp[i][j] = Matrix1[i][j];
			}
			else
			{
				matrixTemp[i][j] = '-';
			}
		}
	}

	// copying the elements from matrixTemp to Matrix2 according
	// to the required format....
	flag1 = false;
	tempColsCount = 0;
	tempRowsCount = 0;
	for (int i = 0; i < rows; i++)
	{
		tempColsCount = 0;
		flag1 = false;
		for (int j = 0; j < cols; j++)
		{
			if (matrixTemp[i][j] != '-')
			{
				flag1 = true;
				Matrix2[tempRowsCount][tempColsCount] = matrixTemp[i][j];
				tempColsCount++;
			}
		}
		if (flag1==true)
		{ 
			for (int i = tempColsCount; i < cols; i++)
			{
				Matrix2[tempRowsCount][tempColsCount] = '-';
				tempColsCount++;
			}
			tempRowsCount++;
		}
	}
	for (int i = tempRowsCount; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Matrix2[i][j] = '-';
		}
	}
}

int main()
{

	char A[rows1][cols];
	char B[rows1][cols];
	char rChar;

	cout << "Enter Elements Of : " << rows1 << " by " << cols << " Matrix\n\n";
	for (int i = 0; i < rows1; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cin >> A[i][j];
		}
	}
	cout << "Enter The Character That You Want To Remove \n\n";
	cin >> rChar;

	cout << "Displaying The Input Array\n\n";
	for (int i = 0; i < rows1; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << A[i][j] << "\t";
		}
		cout << "\n\n";
	}

	RemoveFromMatrix(A, rChar, B, rows1);
	cout << "\n\nDisplaying The Modified Array\n\n";
	for (int i = 0; i < rows1; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << B[i][j] << "\t";
		}
		cout << "\n\n";
	}
	system("pause");
}