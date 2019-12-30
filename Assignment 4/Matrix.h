#include<iostream>
#include<fstream>
using namespace std;
class Matrix
{
private:
	int**matrix;
	int rows,cols;
public:
	int getNumRows();
	int getNumCols();
	int*operator[](int i);
	Matrix();//Default constructor
	Matrix(const Matrix&obj);
	Matrix(int rows, int cols);
	Matrix(char*filename);
	Matrix operator+(const Matrix&obj);
	Matrix operator-(const Matrix&obj);
	Matrix operator=(const Matrix&obj);
	bool operator==(const Matrix&obj);
	Matrix operator*(const Matrix&obj);
	const Matrix& transpose();
	Matrix operator-();//unary operator
	Matrix operator+=(int obj);
	Matrix operator*=(int obj);
};
