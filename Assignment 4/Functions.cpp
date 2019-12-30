#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<time.h>
#include<string.h>
#include<stdio.h>
#include"Matrix.h"
using namespace std;
int Matrix::getNumRows()
{
	return rows;
}
int Matrix::getNumCols()
{
	return cols;
}
Matrix::Matrix()//Default constructor
{
	rows = 0;
	cols = 0;
	matrix = NULL;
}
Matrix::Matrix(const Matrix&obj)//copy constructor
{
	rows = obj.rows;
	cols = obj.cols;
	matrix = new int*[obj.rows];
	for (int i = 0; i < obj.rows; i++)
	{
		matrix[i] = new int[obj.cols];
	}
	for (int i = 0; i < obj.rows; i++)
	{
		for (int j = 0; j < obj.cols; j++)
		{
			matrix[i][j] = obj.matrix[i][j];
		}
	}
}
Matrix::Matrix(int rows1, int cols1)
{
	rows = rows1;
	cols = cols1;
	matrix = new int*[rows1];
	for (int i = 0; i < rows1; i++)
	{
		matrix[i] = new int[cols1];
	}
	srand(unsigned(time(0)));
	for (int i = 0; i < rows1; i++)
	{
		{
			for (int j = 0; j < cols1; j++)
			{
				matrix[i][j] = rand() % 10;
			}
		}
	}
}
Matrix::Matrix(char*filename)
{
	ifstream fin(filename);
	fin >> rows;
	fin >> cols;
	int i = -1, j = 0;
	char temp[50];
	matrix = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new int[cols];
	}
	while (fin.getline(temp, 50))
	{
		j = 0;
		char*token = strtok(temp, ",");
		while (token != nullptr)
		{
			matrix[i][j] = atoi(token);
			token = strtok(nullptr, ",");
			j++;
		}
		i++;
	}
}
Matrix Matrix::operator+(const Matrix&obj)
{
	Matrix temp;
	if (rows == obj.rows&&cols == obj.cols)
	{
		temp.cols = cols;
		temp.rows = rows;
		temp.matrix = new int*[rows];
		for (int i = 0; i < rows; i++)
		{
			temp.matrix[i] = new int[cols];
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				temp.matrix[i][j] = matrix[i][j] + obj.matrix[i][j];
			}
		}
	}
	return temp;
}
Matrix Matrix::operator-(const Matrix&obj)
{
	if (rows == obj.rows&&cols == obj.cols)
	{
		Matrix temp;
		temp.cols = cols;
		temp.rows = rows;
		temp.matrix = new int*[rows];
		for (int i = 0; i < rows; i++)
		{
			temp.matrix[i] = new int[cols];
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				temp.matrix[i][j] = matrix[i][j] - obj.matrix[i][j];
			}
		}
		return temp;
	}
}
Matrix Matrix::operator=(const Matrix&obj)
{
	matrix = new int*[obj.rows];
	rows = obj.rows;
	cols = obj.cols;
	for (int i = 0; i < obj.rows; i++)
	{
		matrix[i] = new int[cols];
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrix[i][j] = obj.matrix[i][j];
		}
	}
	return *this;
}
Matrix::~Matrix()
{
	if (matrix != NULL)
	{
		for (int i = 0; i < rows; i++)
		{
			delete[]matrix[i];
		}
		delete[]matrix;
	}
}
bool Matrix::operator==(const Matrix&obj)
{
	if (rows != obj.rows || cols != obj.cols)
	{
		return false;
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (matrix[i][j] != obj.matrix[i][j])
			{
				return false;
			}
		}
	}
	return true;
}
Matrix Matrix::operator*(const Matrix&obj)
{
	if (cols == obj.rows)
	{
		Matrix temp;
		temp.cols = cols;
		temp.rows = rows;
		temp.matrix = new int*[rows];
		for (int i = 0; i < rows; i++)
		{
			temp.matrix[i] = new int[cols];
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				temp.matrix[i][j] = matrix[i][j] * obj.matrix[j][i];
			}
		}
		return temp;
	}
	return *this;
}
const Matrix& Matrix::transpose()
{
	Matrix temp;
	temp.cols = rows;
	temp.rows = cols;
	temp.matrix = new int*[temp.rows];
	for (int i = 0; i < temp.rows; i++)
	{
		temp.matrix[i] = new int[temp.cols];
	}
	for (int i = 0; i < temp.rows; i++)
	{
		for (int j = 0; j < temp.cols; j++)
		{
			temp.matrix[i][j] = matrix[j][i];
		}
	}
	for (int i = 0; i < rows; i++)
	{
		delete[]matrix[i];
	}
	delete[]matrix;
	*this = temp;
	return temp;
}
Matrix Matrix::operator-()//unary operator
{
	Matrix temp;
	temp.cols = cols;
	temp.rows = rows;
	temp.matrix = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		temp.matrix[i] = new int[cols];
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			temp.matrix[i][j] = matrix[i][j] * -1;
		}
	}
	return temp;
}
Matrix Matrix::operator+=(int obj)
{
	Matrix temp;
	temp.cols = cols;
	temp.rows = rows;
	temp.matrix = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		temp.matrix[i] = new int[cols];
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			temp.matrix[i][j] = matrix[i][j] + obj;
		}
	}
	for (int i = 0; i < rows; i++)
	{
		delete[]matrix[i];
	}
	delete[]matrix;
	*this = temp;
	return temp;
}
Matrix Matrix::operator*=(int obj)
{
	Matrix temp;
	temp.cols = cols;
	temp.rows = rows;
	temp.matrix = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		temp.matrix[i] = new int[cols];
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			temp.matrix[i][j] = matrix[i][j] * obj;
		}
	}
	for (int i = 0; i < rows; i++)
	{
		delete[]matrix[i];
	}
	delete[]matrix;
	*this = temp;
	return temp;
}
int*Matrix::operator[](int i)
{
	return matrix[i];
}


