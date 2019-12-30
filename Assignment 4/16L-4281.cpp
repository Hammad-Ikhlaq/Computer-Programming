#include<iostream>
#include<fstream>
#include"Matrix.h"
using namespace std;
void printMatrix(Matrix m)
{
	for (int i = 0; i < m.getNumRows(); i++)
	{
		for (int j = 0; j < m.getNumCols(); j++)
		{
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}
int main()
{
	Matrix m1;//empty 0x0 matrix
	Matrix m2("Input1.txt"), m3("Input2.txt");//read from files
	Matrix m5(5, 7);//create a 5x7 matrix with random values
	m1 = m2 + m3;//add matrices
	Matrix m4 = m1 - m3;//subtract matrices
	if (m1 == m4)
	{
		cout << "m1 and m4 are equal matrices\n";
	}
	m5 = m1*m4;//matrix multiplication (assume compatability)
	m5.transpose();//convert nxm to mxn matrix
	m2 = -m2;//negates all elements of m2
	m2 += 5;//adds 5 to all elements of m2
	m2 *= 5;//multiplies 5 to all elements of m2
	printMatrix(m1);
	system("pause");
	return 0;
}