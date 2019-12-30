#include<iostream>
#include<ctime>
#include<Windows.h>
using namespace std;
int GetLengthWidth1(int n, int&width)
{
	int i, j;
	if (n % 2 == 0)
	{
		for (i = 1, j = 3; i <= n, j <= n; i++, j++)
		{
			if (i + j == (n / 2))
			{
				width = j;
				return i;
			}

		}

	}
	else if (n % 2 != 0)
	{
		n++;
		for (i = 1, j = 3; i <= n, j <= n; i++, j++)
		{
			if (i + j == (n / 2))
			{
				width = j;
				return i;
			}

		}

		n--;
	}
}
int GetLengthWidth2(int n, int&width)
{
	int i, j;
	if (n % 2 == 0)
	{
		for (i = 1, j = 2; i <= n, j <= n; i++, j++)
		{
			if (i + j == (n / 2))
			{
				width = j;
				return i;
			}

		}

	}
	else if (n % 2 != 0)
	{
		n++;
		for (i = 1, j = 2; i <= n, j <= n; i++, j++)
		{
			if (i + j == (n / 2))
			{
				width = j;
				return i;
			}

		}

		n--;
	}
}
void Checking(int n, int&length, int&width)
{



		length = GetLengthWidth1(n, width);
	if (length != 0 && width != 0)
	{

	}
	else
	{
		length = GetLengthWidth2(n, width);

	}
}
void DrawRec(int length, int width,int n, int*array,int rand)
{
	int blue = 0,red=rand+2;
	while (blue<rand+3)
	{
		int length1 = length + 2;
		int a = 0, z1 = n - 1, z2 = n - 1 ;

		if (n == 1)
		{

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << array[0];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		if (n == 2)
		{
			if (blue == 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << array[1] << "  ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << array[0] << endl;
			}
			else if (blue == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << array[1] << "  ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << array[0] << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << array[1] << "  ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << array[0] << endl;
			}
		}
		if (n == 3)
		{
			 if (blue == a)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << array[z2] << "  ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << array[a] << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				z2--;
				a++;
				cout << array[z1 - 1] << "  ";
				z1--;
			}
			else if (blue == z2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << array[z2] << "  ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << array[a] << endl;
				z2--;
				a++;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << array[z1 - 1] << "  ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				z1--;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << array[z2] << "  ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << array[a] << endl;
				z2--;
				a++;
				cout << array[z1 - 1] << "  ";
				z1--;
			}
		}
		if (n == 4)
		{
			if (blue == z2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << array[z2] << "  ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << array[a] << endl;
				z2--;
				a++;
				cout << array[z1 - 1] << "  ";
				z1--;
				cout << array[a] << endl << endl;
			}
			else if (blue == a)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << array[z2] << "  ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << array[a] << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				z2--;
				a++;
				cout << array[z1 - 1] << "  ";
				z1--;
				cout << array[a] << endl << endl;
			}
			else if (blue == (z1 - 1))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << array[z2] << "  ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << array[a] << endl;
				z2--;
				a++;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << array[z1 - 1] << "  ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				z1--;
				cout << array[a] << endl << endl;
			}
			else if (blue == a + 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << array[z2] << "  ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << array[a] << endl;
				z2--;
				a++;
				cout << array[z1 - 1] << "  ";
				z1--;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << array[a] << endl << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << array[z2] << "  ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << array[a] << endl;
				z2--;
				a++;
				cout << array[z1 - 1] << "  ";
				z1--;
				cout << array[a] << endl << endl;
			}
		}
		if (n == 5)
		{
			 if (blue == a)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << array[a] << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				a++;
				cout << array[z2] << "  ";
				cout << array[a] << endl;
				z2--;
				a++;
				cout << array[z1 - 1] << "  ";
				z1--;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << array[a] << endl<<endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if (blue==z2)
			{
	
				cout << array[a] << endl;

				a++;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << array[z2] << "  ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << array[a] << endl;
				z2--;
				a++;
				cout << array[z1 - 1] << "  ";
				z1--;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << array[a] << endl << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if (blue==a+1)
			{
				cout << array[a] << endl;
				a++;

				cout << array[z2] << "  ";

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << array[a] << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				z2--;
				a++;
				cout << array[z1 - 1] << "  ";
				z1--;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << array[a] << endl << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if (blue==(z1-1))
			{
				cout << array[a] << endl;
				a++;
				cout << array[z2] << "  ";
				cout << array[a] << endl;
				z2--;
				a++;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << array[z1 - 1] << "  ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				z1--;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << array[a] << endl << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if (blue == a + 2)
			{
				cout << array[a] << endl;
				a++;
				cout << array[z2] << "  ";
				cout << array[a] << endl;
				z2--;
				a++;
				cout << array[z1 - 1] << "  ";
				z1--;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << array[a] << endl << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				cout << array[a] << endl;
				a++;
				cout << array[z2] << "  ";
				cout << array[a] << endl;
				z2--;
				a++;
				cout << array[z1 - 1] << "  ";
				z1--;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << array[a] << endl << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
		}
		else if (n % 2 == 0)
		{
			for (int i = 0; i < length1; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (i == 0)
					{
						if (red == a)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
							cout << array[a] << " ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							a++;
						}
						else if (blue == a)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout << array[a] << " ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							a++;
						}
						else
						{
							cout << array[a] << " ";
							a++;
						}
					}
					else if (i == length1 - 1)
					{
						if (red == z1 - (length1 - 2))
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
							cout << array[z1 - (length1 - 2)] << " ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							z1--;
						}
						else if (blue == z1 - (length1 - 2))
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout << array[z1 - (length1 - 2)] << " ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							z1--;
						}
						else
						{
							cout << array[z1 - (length1 - 2)] << " ";
							z1--;
						}

					}
					else if (j == 0 && n <= 6)
					{
						if (red == a)
						{
							cout << array[z2];
							for (int k = 0; k < width - 1; k++)
							{
								cout << "   ";
							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
							cout << array[a] << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							z2--;
							a++;
						}
						else if (red == z2)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
							cout << array[z2];
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							for (int k = 0; k < width - 1; k++)
							{
								cout << "   ";
							}

							cout << array[a] << endl;

							z2--;
							a++;
						}
						else if (blue == a)
						{
							cout << array[z2];
							for (int k = 0; k < width - 1; k++)
							{
								cout << "   ";
							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout << array[a] << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							z2--;
							a++;
						}
						else if (blue == z2)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout << array[z2];
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							for (int k = 0; k < width - 1; k++)
							{
								cout << "   ";
							}

							cout << array[a] << endl;

							z2--;
							a++;
						}
						else
						{
							cout << array[z2];
							for (int k = 0; k < width - 1; k++)
							{
								cout << "   ";
							}
							cout << array[a] << endl;
							z2--;
							a++;
						}
					}
					else if (j == 0)
					{
						if (red == a)
						{
							cout << array[z2];
							for (int k = 0; k < width - 2; k++)
							{
								cout << "   ";
							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
							cout << array[a] << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							z2--;
							a++;
						}
						else if (red == z2&&blue==a)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
							cout << array[z2];
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							for (int k = 0; k < width - 2; k++)
							{
								cout << "   ";
							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout << array[a] << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							z2--;
							a++;
						}
						else if (red == z2)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
							cout << array[z2];
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							for (int k = 0; k < width - 2; k++)
							{
								cout << "   ";
							}
							cout << array[a] << endl;
							z2--;
							a++;
						}
						else if (blue==a)
						{
							cout << array[z2];
							for (int k = 0; k < width - 2; k++)
							{
								cout << "   ";
							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout << array[a] <<endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							z2--;
							a++;
						}
						else if (blue == z2)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout << array[z2];
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							for (int k = 0; k < width - 2; k++)
							{
								cout << "   ";
							}
		
							cout << array[a] << endl;

							z2--;
							a++;
						}
						else
						{
							cout << array[z2];
							for (int k = 0; k < width - 2; k++)
							{
								cout << "   ";
							}
							cout << array[a] << endl;
							z2--;
							a++;
						}
					}

				}
				cout << endl;
			}
		}
		else
		{
			for (int i = 0; i < length1; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (i == 0)
					{
						if (red == a)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
							cout << array[a] << " ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							a++;
						}
						else if (blue == a)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout << array[a] << " ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							a++;
						}
						else
						{
							cout << array[a] << " ";
							a++;
						}
					}
					else if (i == length1 - 1 && j != width - 2)
					{
						if (red == z1 - (length1 - 2))
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
							cout << array[z1 - (length1 - 2)] << " ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							z1--;
						}
						else if (blue == z1 - (length1 - 2))
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout << array[z1 - (length1 - 2)] << " ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							z1--;
						
						}
						else
						{
							cout << array[z1 - (length1 - 2)] << " ";
							z1--;
						}

					}
					else if (j == 0 && n <= 6)
					{
						if (red == a)
						{
							cout << array[z2];
							for (int k = 0; k < width - 1; k++)
							{
								cout << "   ";
							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
							cout << array[a] << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							z2--;
							a++;
						}
						else if (red == z2)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
							cout << array[z2];
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							for (int k = 0; k < width - 1; k++)
							{
								cout << "   ";
							}

							cout << array[a] << endl;

							z2--;
							a++;
						}
						else if (blue == a)
						{
							cout << array[z2];
							for (int k = 0; k < width - 1; k++)
							{
								cout << "   ";
							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout << array[a] << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							z2--;
							a++;
						}
						else if (blue == z2)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout << array[z2];
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							for (int k = 0; k < width - 1; k++)
							{
								cout << "   ";
							}

							cout << array[a] << endl;

							z2--;
							a++;
						}
						else
						{
							cout << array[z2];
							for (int k = 0; k < width - 2; k++)
							{
								cout << "   ";
							}
							cout << array[a] << endl;
							z2--;
							a++;
						}
					}
					else if (j == 0)
					{
						if (red == a)
						{
							cout << array[z2];
							for (int k = 0; k < width - 2; k++)
							{
								cout << "   ";
							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
							cout << array[a] << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							z2--;
							a++;
						}
						else if (red == z2&&blue == a)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
							cout << array[z2];
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							for (int k = 0; k < width - 2; k++)
							{
								cout << "   ";
							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout << array[a] << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							z2--;
							a++;
						}
						else if (red == z2)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
							cout << array[z2];
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							for (int k = 0; k < width - 2; k++)
							{
								cout << "   ";
							}
							cout << array[a] << endl;
							z2--;
							a++;
						}
						else if (blue == a)
						{
							cout << array[z2];
							for (int k = 0; k < width - 2; k++)
							{
								cout << "   ";
							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout << array[a] << endl;
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							z2--;
							a++;
						}
						else if (blue == z2)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
							cout << array[z2];
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							for (int k = 0; k < width - 2; k++)
							{
								cout << "   ";
							}

							cout << array[a] << endl;

							z2--;
							a++;
						}
						else
						{
							cout << array[z2];
							for (int k = 0; k < width - 2; k++)
							{
								cout << "   ";
							}
							cout << array[a] << endl;
							z2--;
							a++;
						}
					}

				}
				cout << endl;
			}
		}
		blue++;
		cout << endl;
		Sleep(500);
		//system("cls");
	}
}
int*extendByrand(int*arr1, int&n,int max)
{
	int i = 0,j;
	srand(unsigned(time(0)));
	int r = (rand() % 9+2);
	int*arr2 = new int[n + r];
	for ( i = 0; i < n; i++)
	{
		arr2[i] = arr1[i];
	}
	cout << "extention!=\t"<<r<<endl<<endl;
	delete[]arr1;
	for ( i = n,j=max+1; i <r+n; i++,j++)
	{
		arr2[i] =  j; 
	}
	n = n + r;
	return arr2;
}
void bubble_sort(int list[], int n)
{
  long c, d, t;
 
  for (c = 0 ; c < ( n - 1 ); c++)
  {
    for (d = 0 ; d < n - c - 1; d++)
    {
      if (list[d] > list[d+1])
      {
        t         = list[d];
        list[d]   = list[d+1];
        list[d+1] = t;
      }
    }
  }
}
int*makeIntArray(int n)
{
	if(n==0)
		return nullptr;
	return new int[n];
}
int*shrinkBy1(int*arr1, int &n)
{
	int*arr2=nullptr;
	n=n-1;
	arr2=makeIntArray(n);
	for (int i = 0; i < n; i++)
	{
		arr2[i] = arr1[i];
	}
	delete[]arr1;
	return arr2;
}
int main()
{
	int n=0,p=0,r=0,length=0,width=0;
	int k = 0;
	while (k!=1)
	{
		cout << "input the number of people\n";
		cin >> n;
		system("cls");
		if (n == 1)
		{
			cout << "1 is the winner\n";
		}
		int z = n;
		k = n;
		int*array1 = new int[n];
		for (int i = 0; i < n ; i++)
		{
			array1[i] = i+1;
		}
		Checking(n, length, width);
		r = rand() % (2*k)+1 ;
		r = r % 10;
		DrawRec(length, width, n,array1,r);
		//system("cls");
				p = rand() % 8 + 5;
				int q = 1;
				while (k != 1)
				{
					p = rand() % 8 + 5;
					length = 0, width = 0;
					r = rand() % (2 * k) ;
					r++;
					r = r % 10;
					if (k>=6&&k<=9)
					{
						r = r - 2;
					}
						for (int i = r; i < k - 1; i++)
						{
							swap(array1[i], array1[i + 1]);
						}
						array1 = shrinkBy1(array1, k);
						cout << endl;
						Checking(k,length,width);
						if (q == p)
						{
							array1 = extendByrand(array1, k, z);
							q++;
						}
						q++;
						DrawRec(length, width, k, array1,r);
						if (k >= 6 && k <= 9)
						{
							r = r + 2;
						}
						Sleep(500);
						//system("cls");
						cout << endl;
						
						if (k == 1)
						{
							break;
						}
				}
		cout << "the winner is " << array1[k-1]<<endl;
		delete[]array1;
	}
	system("pause");
	return 0;
}